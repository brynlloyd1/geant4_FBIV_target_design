#ifndef brynDetectorConstruction_COREHOLE_hh
#define brynDetectorConstruction_COREHOLE_hh

#include "brynDetectorConstruction.hh"

class brynDetectorConstruction_COREHOLE : public brynDetectorConstruction {
    public:
        // dont need to write constructor or destructor since they are written in the base class

        // Construct() returns an instance of G4VPhysicalVolume. It is a virtual method, so we have to overwrite it
        virtual G4VPhysicalVolume* Construct() override;
};
#endif
