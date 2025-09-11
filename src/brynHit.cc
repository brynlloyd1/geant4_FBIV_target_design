#include "brynHit.hh"


// virtual methods
void brynHit::Draw() {;}
void brynHit::Print() {;}

// methods to collect information
void brynHit::setParticleName(G4String particleName) {
    this->particleName = particleName;
}

void brynHit::setPosition(G4ThreeVector position) {
    this->position = position;
}

void brynHit::setSpeed(G4double speed) {
    this->speed = speed;
}

void brynHit::setMagMomentum(G4double magMomentum) {
    this->magMomentum = magMomentum;
}

void brynHit::setKineticEnergy(G4double kineticEnergy) {
    this->kineticEnergy = kineticEnergy;
}

void brynHit::setDirection(G4ThreeVector direction) {
    this->direction = direction;
}

G4String brynHit::getParticleName() {
    return this->particleName;
}

G4ThreeVector brynHit::getPosition() {
    return this->position;
}

G4double brynHit::getSpeed() {
    return this->speed;
}

G4double brynHit::getMagMomentum() {
    return this->magMomentum;
}

G4double brynHit::getKineticEnergy() {
    return this->kineticEnergy;
}

G4ThreeVector brynHit::getDirection() {
    return this->direction;
}
