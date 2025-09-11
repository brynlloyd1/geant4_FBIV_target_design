#ifndef brynHit_hh
#define brynHit_hh

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"

class brynHit : public G4VHit {
public:
    brynHit() = default;
    ~brynHit() = default;

    // virtual methods
    void Draw() override;
    void Print() override;

    // methods to collect information
    void setParticleName(G4String particleName);
    void setPosition(G4ThreeVector position);
    void setSpeed(G4double speed);
    void setMagMomentum(G4double magMomentum);
    void setKineticEnergy(G4double kineticEnergy);
    void setDirection(G4ThreeVector direction);
    G4String getParticleName();
    G4ThreeVector getPosition();
    G4double getSpeed();
    G4double getMagMomentum();
    G4double getKineticEnergy();
    G4ThreeVector getDirection();

private:
    G4String particleName;
    G4ThreeVector position;
    G4double speed;
    G4double magMomentum;
    G4double kineticEnergy;
    G4ThreeVector direction;
};


// G4THitsCollection is a template class, so this is basically how you write ur own class on top of it
using brynHitsCollection = G4THitsCollection<brynHit>;
#endif
