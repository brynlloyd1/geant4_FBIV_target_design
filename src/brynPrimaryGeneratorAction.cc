#include "brynPrimaryActionGenerator.hh"

#include "CLHEP/Random/RandGauss.h"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemofUnits.hh"


brynPrimaryGeneratorAction::brynPrimaryGeneratorAction() {

    // create gun and set number of particles per beamOn
    G4int nParticles = 1;
    particleGun = new G4ParticleGun(nParticles);

    // set particle definition - proton is already available
    const G4String& particleName = "proton";
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particleDefinition = particleTable->FindParticle(particleName);
    particleGun->SetParticleDefinition(particleDefinition);

    // sets direction of beam
    G4ThreeVector momentum = G4ThreeVector(0., 0., 1.);
    particleGun->SetParticleMomentumDirection(momentum);
}

brynPrimaryGeneratorAction::~brynPrimaryGeneratorAction() {
    delete particleGun;
}


/// must generate random numbers here, and not in the constructor!!
void brynPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {

    // generate random position
    G4double sigmaR = 0.003*m;
    G4double x0 = CLHEP::RandGauss::shoot(0.0, sigmaR);
    G4double y0 = CLHEP::RandGauss::shoot(0.0, sigmaR);
    particleGun->SetParticlePosition(G4ThreeVector(x0, y0, -1.0*m));

    // generate random energy
    // Charlie - width corresponding to 0.03% of the central energy
    G4double centralEnergy = 440 * GeV;
    G4double sigmaEnergy = 0.0003 * centralEnergy;
    G4double energy = CLHEP::RandGauss::shoot(centralEnergy, sigmaEnergy);
    particleGun->SetParticleEnergy(energy);

    particleGun->GeneratePrimaryVertex(anEvent);
}
