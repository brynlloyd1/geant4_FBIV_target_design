#include "brynDetectorConstruction.hh"
#include "brynSensitiveDetector.hh"

// imports for materials
#include "G4NistManager.hh"
// #include "G4Material.hh"

// imports for volumes
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

G4VPhysicalVolume* brynDetectorConstruction::Construct() {

    ////////////////////////
    // defining materials //
    ////////////////////////
    G4NistManager* NistManager = G4NistManager::Instance();

    G4Material* vacuumMaterial = NistManager->FindOrBuildMaterial("G4_Galactic");
    G4Material* graphiteMaterial = NistManager->FindOrBuildMaterial("G4_GRAPHITE");
    G4Material* tantalumMaterial = NistManager->FindOrBuildMaterial("G4_Ta");
    G4Material* detectorMaterial = NistManager->FindOrBuildMaterial("G4_Galactic");

    ///////////////////////
    // setup of geometry //
    ///////////////////////

    G4bool checkOverlaps = true;

    // world
    G4VSolid* solidWorld = new G4Box("solidWorld", 5.0*m, 5.0*m, 5.0*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, vacuumMaterial, "logicWorld");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld,"logicWorld", 0, false, 0, checkOverlaps);

    // target
    G4VSolid* solidGraphite = new G4Tubs("solidGraphite", 0.*m, 0.014*m, 0.7*m, 0., 360.0*deg);
    G4LogicalVolume* logicGraphite = new G4LogicalVolume(solidGraphite, graphiteMaterial, "logicGraphite");
    G4VPhysicalVolume* physGraphite = new G4PVPlacement(0, G4ThreeVector(), logicGraphite, "logicGraphite", logicWorld, false, 0, checkOverlaps);

    //detector
    G4ThreeVector detectorPosition = G4ThreeVector(0.*m, 0.*m, 0.701*m);
    G4VSolid* solidDetector = new G4Tubs("solidDetector", 0.*m, 0.014*m, 0.001*m, 0., 360.0*deg);
    logicDetector = new G4LogicalVolume(solidDetector, detectorMaterial, "logicDetector");
    G4VPhysicalVolume* physDetector = new G4PVPlacement(0, detectorPosition, logicDetector, "logicDetector", logicWorld, false, 0, checkOverlaps);


    //                                        
    // Visualization attributes
    logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

    G4VisAttributes* graphiteVisAtt= new G4VisAttributes(G4Colour::Blue());
    graphiteVisAtt->SetVisibility(true);
    graphiteVisAtt->SetForceSolid(true);
    logicGraphite->SetVisAttributes(graphiteVisAtt);

    G4VisAttributes* detectorVisAtt= new G4VisAttributes(G4Colour::White());
    detectorVisAtt->SetVisibility(true);
    detectorVisAtt->SetForceWireframe(true);
    logicDetector->SetVisAttributes(detectorVisAtt);

    return physWorld;
}

void brynDetectorConstruction::ConstructSDandField() {
    brynSensitiveDetector* sensitiveDetector = new brynSensitiveDetector("sensitiveDetector", "fHitsCollection");
    logicDetector->SetSensitiveDetector(sensitiveDetector);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensitiveDetector);
}
