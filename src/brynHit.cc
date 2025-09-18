#include "brynHit.hh"


// virtual methods
void brynHit::Draw() {;}
void brynHit::Print() {;}


void brynHit::setParticleName(G4String particleName) {
    this->particleName = particleName;
}

void brynHit::setPosition(G4ThreeVector position) {
    this->position = position;
}

void brynHit::setKineticEnergy(G4double kineticEnergy) {
    this->kineticEnergy = kineticEnergy;
}

void brynHit::setDirection(G4ThreeVector direction) {
    this->direction = direction;
}

void brynHit::setOrigin(G4String origin) {
    this->origin = origin;
}


G4String brynHit::getParticleName() {
    return this->particleName;
}

G4ThreeVector brynHit::getPosition() {
    return this->position;
}

G4double brynHit::getKineticEnergy() {
    return this->kineticEnergy;
}

G4ThreeVector brynHit::getDirection() {
    return this->direction;
}

G4String brynHit::getOrigin() {
    return this->origin;
}
