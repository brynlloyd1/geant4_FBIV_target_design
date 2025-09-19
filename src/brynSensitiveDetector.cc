#include "brynHit.hh"
#include "brynSensitiveDetector.hh"
#include "brynTrackInformation.hh"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Threading.hh"
#include "G4ThreeVector.hh"
#include "G4VSensitiveDetector.hh"

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
    if (!step->IsFirstStepInVolume()) return false;

    G4Track* track = step->GetTrack();
    G4String particleName = track->GetDefinition()->GetParticleName();

    // particle ancestry stuff
    std::string ancestryString = "unknown";
    if (particleName == "e-" || particleName == "e+") {
        auto info = dynamic_cast<brynTrackInformation*>(track->GetUserInformation());
        if (info) {
            const auto& ancestry = info->GetAncestry();

            std::ostringstream ancestryStr;
            for (size_t i=0; i<ancestry.size(); i++) {
                ancestryStr << ancestry[i];
                if (i < ancestry.size() - 1) ancestryStr << "_";

            ancestryString = ancestryStr.str();
            }
        }
    }

    // get data from the track
    G4double kineticEnergy = track->GetKineticEnergy();
    G4ThreeVector momentumDirection = track->GetMomentumDirection();
    G4ThreeVector position = track->GetPosition();

    // add information to the hit
    brynHit* hit = new brynHit();
    hit->setParticleName(particleName);
    hit->setPosition(position);
    hit->setKineticEnergy(kineticEnergy);
    hit->setDirection(momentumDirection);
    hit->setAncestry(ancestryString);

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
        outFile << "particleName,x[m],y[m],z[m],kineticEnergy[MeV],dir_x,dir_y,dir_z,ancestry\n";
        threadsWithHeader.insert(threadID);
    }

    for (size_t i=0; i<fHitsCollection->entries(); i++) {
        brynHit* hit = (*fHitsCollection)[i];

        G4String particleName = hit->getParticleName();
        G4ThreeVector position = hit-> getPosition();
        G4double kineticEnergy = hit->getKineticEnergy();
        G4ThreeVector direction = hit->getDirection();
        G4String ancestryString = hit->getAncestry();

        std::stringstream ss;
        ss
            << particleName                 << ","
            << position.x() / m             << ","
            << position.y() / m             << ","
            << position.z() / m             << ","
            << kineticEnergy / MeV          << ","
            << direction.x()                << ","
            << direction.y()                << ","
            << direction.z()                << ","
            << ancestryString;
        std::string line = ss.str();
        outFile << line << "\n";
    }
    outFile.close();
}
