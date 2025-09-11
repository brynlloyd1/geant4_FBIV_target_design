#ifndef brynDetectorConstruction_FBIII_hh
#define brynDetectorConstruction_FBIII_hh

#include "brynDetectorConstruction.hh"

class brynDetectorConstruction_FBIII : public brynDetectorConstruction {
    public:
        // dont need to write constructor or destructor since they are written in the base class

        // Construct() returns an instance of G4VPhysicalVolume. It is a virtual method, so we have to overwrite it
        virtual G4VPhysicalVolume* Construct() override;
};
#endif
