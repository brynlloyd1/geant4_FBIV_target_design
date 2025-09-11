#include "brynDetectorConstruction.hh"
#include "brynSensitiveDetector.hh"
#include "G4SDManager.hh"

void brynDetectorConstruction::ConstructSDandField() {
    brynSensitiveDetector* sensitiveDetector = new brynSensitiveDetector("sensitiveDetector", "fHitsCollection");
    logicDetector->SetSensitiveDetector(sensitiveDetector);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensitiveDetector);
}
