#include "brynSensitiveDetector.hh"
#include "brynHit.hh"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include <CLHEP/Units/PhysicalConstants.h>
#include <CLHEP/Units/SystemOfUnits.h>
#include <G4StepStatus.hh>
#include <G4Threading.hh>
#include <G4ThreeVector.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VSensitiveDetector.hh>
#include "G4SystemOfUnits.hh"

#include <fstream>
#include <sstream>
#include <unordered_set>

brynSensitiveDetector::brynSensitiveDetector(const G4String& name,
                                             const G4String& hitsCollectionName) : G4VSensitiveDetector(name) {
    collectionName.insert(hitsCollectionName);
}

void brynSensitiveDetector::Initialize(G4HCofThisEvent* hitsCollection) {
    // called when the sensitive detector is initialised at the start of an event
    // initialise data structures that will hold particle type, energy, etc.

    fHitsCollection = new brynHitsCollection(SensitiveDetectorName, collectionName[0]);
    G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hitsCollection->AddHitsCollection(hcID, fHitsCollection);
}

/// from geant4 docs -> G4TouchableHistory* is obsolete and not used
/// return value is not used by geant4, so is up to me if I want to use this in any way
G4bool brynSensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history) {

    // only process the first step in the volume
    if (!step->IsFirstStepInVolume()) {
        return false;
    }

    G4VPhysicalVolume* physicalVolume = step->GetPreStepPoint()->GetPhysicalVolume();


    G4Track* track = step->GetTrack();

    // get data from the track
    G4String particleName = track->GetDefinition()->GetParticleName();
    G4double kineticEnergy = track->GetKineticEnergy();
    G4ThreeVector momentumDirection = track->GetMomentumDirection();
    G4ThreeVector momentum = track->GetMomentum();
    G4ThreeVector position = track->GetPosition();
    G4double speed = track->GetVelocity();

    // process track data into information about the hit
    G4double magMomentum = momentum.mag();

    // add information to the hit
    brynHit* hit = new brynHit();
    hit->setParticleName(particleName);
    hit->setPosition(position);
    hit->setSpeed(speed);
    hit->setMagMomentum(magMomentum);
    hit->setKineticEnergy(kineticEnergy);
    hit->setDirection(momentumDirection);

    // add hit to the hit collection
    fHitsCollection->insert(hit);
    return true;
}



/// writes data to csv file
/// HOWEVER, in multithreading mode, different threads try to write to a csv file at the same time, messing up lines
/// this writes a temp file for each thread, so this issue doesnt happen
void brynSensitiveDetector::EndOfEvent(G4HCofThisEvent* hitsCollection) {

    G4int threadID = G4Threading::G4GetThreadId();
    std::stringstream filenameStream;
    filenameStream << "tmp_files/beam_data_thread" << threadID << ".csv";
    std::string filename = filenameStream.str();

    static std::unordered_set<G4int> threadsWithHeader;

    std::ofstream outFile(filename, std::ios::app);
    if (!outFile) {
        std::cerr << "Error opening file\n";
    }

    if (threadsWithHeader.find(threadID) == threadsWithHeader.end()) {
        outFile << "particleName,x[m],y[m],z[m],v[m/s],p[MeV/c],kineticEnergy[MeV],dir_x,dir_y,dir_z\n";
        threadsWithHeader.insert(threadID);
    }

    for (size_t i=0; i<fHitsCollection->entries(); i++) {
        brynHit* hit = (*fHitsCollection)[i];
        G4String particleName = hit->getParticleName();
        G4ThreeVector position = hit-> getPosition();
        G4double speed = hit->getSpeed();
        G4double magMomentum = hit->getMagMomentum();
        G4double kineticEnergy = hit->getKineticEnergy();
        G4ThreeVector direction = hit->getDirection();


        std::stringstream ss;
        ss
            << particleName                 << ","
            << position.x() / m             << ","
            << position.y() / m             << ","
            << position.z() / m             << ","
            << speed / (m/s)                << ","
            << magMomentum                  << ","
            << kineticEnergy / MeV          << ","
            << direction.x()                << ","
            << direction.y()                << ","
            << direction.z();
        std::string line = ss.str();

        outFile << line << "\n";

    }
    outFile.close();
}
