#include "brynDetectorConstruction_FBIISPLIT.hh"

#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"


G4VPhysicalVolume* brynDetectorConstruction_FBIISPLIT::Construct() {

    ////////////////////////
    // defining materials //
    ////////////////////////
    G4NistManager* NistManager = G4NistManager::Instance();

    G4Material* vacuumMaterial = NistManager->FindOrBuildMaterial("G4_Galactic");
    G4Material* graphiteMaterial = NistManager->FindOrBuildMaterial("G4_GRAPHITE");
    G4Material* tantalumMaterial = NistManager->FindOrBuildMaterial("G4_Ta");
    G4Material* detectorMaterial = NistManager->FindOrBuildMaterial("G4_Galactic");
    G4Material* airMaterial = NistManager->FindOrBuildMaterial("G4_AIR");
    G4Material* aluminiumMaterial = NistManager->FindOrBuildMaterial("G4_Al");

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

    G4double graphite1Thickness = 180.*mm;
    G4double graphite2Thickness = 180.*mm;
    G4double tantalumThickness = 10.*mm;
    G4double totalLength = 1400.*mm;
    G4double aluminiumLength = totalLength - graphite1Thickness - graphite2Thickness - tantalumThickness;

    G4double targetRadius = 14.*mm;
    G4double aluminiumRadialThickness = 10.*mm;

    // graphite 1
    G4ThreeVector graphite1Position = G4ThreeVector(0, 0, 0.5*graphite1Thickness);
    G4VSolid* solidGraphite1 = new G4Tubs("solidGraphite1", 0.*m, targetRadius, 0.5*graphite1Thickness, 0., 360.0*deg);
    G4LogicalVolume* logicGraphite1 = new G4LogicalVolume(solidGraphite1, charlieGraphiteMaterial, "logicGraphite1");
    G4VPhysicalVolume* physGraphite1 = new G4PVPlacement(0, graphite1Position, logicGraphite1, "logicGraphite1", logicWorld, false, 0, checkOverlaps);

    // air between graphite sections
    // G4ThreeVector airPosition = G4ThreeVector(0., 0., 180.+(1400. - 370.)*0.5*mm);
    // G4VSolid* solidAir = new G4Tubs("solidAir", 0., 0.01*m, (1400.-370.)*0.5*mm, 0., 360.0*deg);
    // G4LogicalVolume *logicAir = new G4LogicalVolume(solidAir, airMaterial, "logicAir");
    // G4VPhysicalVolume* physAir = new G4PVPlacement(0, airPosition, logicAir, "logicAir", logicWorld, false, 0, checkOverlaps);
    
    G4double aluminiumZPosition = graphite1Thickness + 0.5*aluminiumLength;
    G4ThreeVector aluminiumPosition = G4ThreeVector(0, 0, aluminiumZPosition);
    G4VSolid* solidAluminium = new G4Tubs("solidAluminium", targetRadius - aluminiumRadialThickness, targetRadius, 0.5*aluminiumLength, 0., 360*deg);
    G4LogicalVolume* logicAluminium = new G4LogicalVolume(solidAluminium, aluminiumMaterial, "logicAluminium");
    G4VPhysicalVolume* physAluminium = new G4PVPlacement(0, aluminiumPosition, logicAluminium, "logicAluminium", logicWorld, false, 0, checkOverlaps);
    G4VisAttributes* AlVisAtt= new G4VisAttributes(G4Colour::Red());
    AlVisAtt->SetVisibility(true);
    AlVisAtt->SetForceWireframe(true);
    logicAluminium->SetVisAttributes(AlVisAtt);




    // graphite 2
    G4double graphite2ZPosition = totalLength - tantalumThickness - 0.5*graphite2Thickness;
    G4ThreeVector graphite2Position = G4ThreeVector(0., 0., graphite2ZPosition);
    G4VSolid* solidGraphite2 = new G4Tubs("solidGraphite2", 0.*m, targetRadius, 0.5*graphite2Thickness, 0., 360.0*deg);
    G4LogicalVolume* logicGraphite2 = new G4LogicalVolume(solidGraphite2, charlieGraphiteMaterial, "logicGraphite2");
    G4VPhysicalVolume* physGraphite2 = new G4PVPlacement(0, graphite2Position, logicGraphite2, "logicGraphite2", logicWorld, false, 0, checkOverlaps);

    // tantalum
    if (tantalumThickness > 0.) {
        G4double tantalumZPosition = totalLength - 0.5*tantalumThickness;
        G4ThreeVector tantalumPosition = G4ThreeVector(0.*m, 0.*m, tantalumZPosition);
        G4VSolid* solidTantalum = new G4Tubs("solidTantalum", 0.*m, targetRadius, 0.5*tantalumThickness, 0., 360.0*deg);
        G4LogicalVolume* logicTantalum = new G4LogicalVolume(solidTantalum, tantalumMaterial, "logicTantalum");
        G4VPhysicalVolume* physTantalum = new G4PVPlacement(0, tantalumPosition, logicTantalum, "logicTantalum", logicWorld, false, 0, checkOverlaps);

        G4VisAttributes* tantalumVisAtt= new G4VisAttributes(G4Colour::Magenta());
        tantalumVisAtt->SetVisibility(true);
        tantalumVisAtt->SetForceSolid(true);
        logicTantalum->SetVisAttributes(tantalumVisAtt);
    }
    //detector
    G4ThreeVector detectorPosition = G4ThreeVector(0.*m, 0.*m, (totalLength + 0.5)*mm);
    G4VSolid* solidDetector = new G4Tubs("solidDetector", 0.*m, 0.05*m, 0.001*m, 0., 360.0*deg);
    logicDetector = new G4LogicalVolume(solidDetector, detectorMaterial, "logicDetector");
    G4VPhysicalVolume* physDetector = new G4PVPlacement(0, detectorPosition, logicDetector, "logicDetector", logicWorld, false, 0, checkOverlaps);


    //                                        
    // Visualization attributes
    logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

    G4VisAttributes* graphiteVisAtt= new G4VisAttributes(G4Colour::Blue());
    graphiteVisAtt->SetVisibility(true);
    graphiteVisAtt->SetForceSolid(true);
    logicGraphite1->SetVisAttributes(graphiteVisAtt);
    logicGraphite2->SetVisAttributes(graphiteVisAtt);


    G4VisAttributes* detectorVisAtt= new G4VisAttributes(G4Colour::White());
    detectorVisAtt->SetVisibility(true);
    detectorVisAtt->SetForceWireframe(true);
    logicDetector->SetVisAttributes(detectorVisAtt);


    return physWorld;
}
