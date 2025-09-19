#include "brynDetectorConstruction_FBII.hh"

#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"


G4VPhysicalVolume* brynDetectorConstruction_FBII::Construct() {

    ////////////////////////
    // defining materials //
    ////////////////////////
    G4NistManager* NistManager = G4NistManager::Instance();

    G4Material* vacuumMaterial = NistManager->FindOrBuildMaterial("G4_Galactic");
    G4Material* graphiteMaterial = NistManager->FindOrBuildMaterial("G4_GRAPHITE");
    G4Material* tantalumMaterial = NistManager->FindOrBuildMaterial("G4_Ta");
    G4Material* detectorMaterial = NistManager->FindOrBuildMaterial("G4_Galactic");

    // Charlies thesis uses 1.84 g/cc (guessing thats the default in fluka, but have to manually create that here)
    G4Element* C = NistManager->FindOrBuildElement("C");
    G4Material* charlieGraphiteMaterial = new G4Material("charlieGraphite", 1.84 * g/cm3, 1);
    charlieGraphiteMaterial->AddElement(C, 1);


    ///////////////////////
    // setup of geometry //
    ///////////////////////
    G4bool checkOverlaps = true;

    // world
    G4VSolid* solidWorld = new G4Box("solidWorld", 5.0*m, 5.0*m, 5.0*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, vacuumMaterial, "logicWorld");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld,"logicWorld", 0, false, 0, checkOverlaps);

    // graphite
    G4VSolid* solidGraphite = new G4Tubs("solidGraphite", 0.*m, 0.01*m, 0.18*m, 0., 360.0*deg);
    G4LogicalVolume* logicGraphite = new G4LogicalVolume(solidGraphite, charlieGraphiteMaterial, "logicGraphite");
    G4VPhysicalVolume* physGraphite = new G4PVPlacement(0, G4ThreeVector(), logicGraphite, "logicGraphite", logicWorld, false, 0, checkOverlaps);

    // tantalum
    G4ThreeVector tantalumPosition = G4ThreeVector(0.*m, 0.*m, 0.185*m);
    G4VSolid* solidTantalum = new G4Tubs("solidTantalum", 0.*m, 0.01*m, 0.005*m, 0., 360.0*deg);
    G4LogicalVolume* logicTantalum = new G4LogicalVolume(solidTantalum, tantalumMaterial, "logicTantalum");
    G4VPhysicalVolume* physTantalum = new G4PVPlacement(0, tantalumPosition, logicTantalum, "logicTantalum", logicWorld, false, 0, checkOverlaps);

    //detector
    G4ThreeVector detectorPosition = G4ThreeVector(0.*m, 0.*m, 0.191*m);
    G4VSolid* solidDetector = new G4Tubs("solidDetector", 0.*m, 0.01*m, 0.001*m, 0., 360.0*deg);
    logicDetector = new G4LogicalVolume(solidDetector, detectorMaterial, "logicDetector");
    G4VPhysicalVolume* physDetector = new G4PVPlacement(0, detectorPosition, logicDetector, "logicDetector", logicWorld, false, 0, checkOverlaps);


    //                                        
    // Visualization attributes
    logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

    G4VisAttributes* graphiteVisAtt= new G4VisAttributes(G4Colour::Blue());
    graphiteVisAtt->SetVisibility(true);
    graphiteVisAtt->SetForceSolid(true);
    logicGraphite->SetVisAttributes(graphiteVisAtt);

    G4VisAttributes* tantalumVisAtt= new G4VisAttributes(G4Colour::Magenta());
    tantalumVisAtt->SetVisibility(true);
    tantalumVisAtt->SetForceSolid(true);
    logicTantalum->SetVisAttributes(tantalumVisAtt);

    G4VisAttributes* detectorVisAtt= new G4VisAttributes(G4Colour::White());
    detectorVisAtt->SetVisibility(true);
    detectorVisAtt->SetForceWireframe(true);
    logicDetector->SetVisAttributes(detectorVisAtt);


    return physWorld;
}
