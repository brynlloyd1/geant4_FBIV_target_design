#include "brynDetectorConstruction_TESTING.hh"

#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"


struct TargetSegment {
    G4String name;
    G4double fullLength;
    G4Material* material;
};



G4VPhysicalVolume* brynDetectorConstruction_TESTING::Construct() {

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

    std::vector<G4LogicalVolume*> graphiteLogicalVolumes;
    std::vector<G4LogicalVolume*> tantalumLogicalVolumes;




    G4int nSegments = 4;
    G4double totalLength = 1.4*m;
    G4double tantalumThickness = 0.01*m;



    std::vector<TargetSegment> targetSegments;

    for (G4int n=0; n<nSegments; n++) {
        G4double graphiteThickness = totalLength/nSegments - tantalumThickness;
        targetSegments.push_back({"graphite_"+std::to_string(n), graphiteThickness, graphiteMaterial});
        targetSegments.push_back({"tantalum_"+std::to_string(n), tantalumThickness, tantalumMaterial});
    }

    G4double targetRadius = 0.014 * m;
    G4double currentZ = 0.0*m;

    for (size_t i = 0; i < targetSegments.size(); i++) {
        const TargetSegment& segment = targetSegments[i];

        G4VSolid* solid = new G4Tubs(segment.name+"_solid", 0.*mm, targetRadius, segment.fullLength/2.0, 0., 360*deg);
        G4LogicalVolume* logical = new G4LogicalVolume(solid, segment.material, segment.name+"_logic");
        G4double zPosition = currentZ + segment.fullLength/2.0;
        G4VPhysicalVolume* physical = new G4PVPlacement(0,
                                                        G4ThreeVector(0., 0., zPosition),
                                                        logical,
                                                        segment.name+"_logic",
                                                        logicWorld,
                                                        false,
                                                        0,
                                                        checkOverlaps);

        // append logical volume for collection, to assign visAttributes to
        if (segment.material == graphiteMaterial) {
            graphiteLogicalVolumes.push_back(logical);
        } else {
            tantalumLogicalVolumes.push_back(logical);
        }


        currentZ += segment.fullLength;
    }
 
    //detector
    G4ThreeVector detectorPosition = G4ThreeVector(0.*m, 0.*m, totalLength + 0.001*m);
    G4VSolid* solidDetector = new G4Tubs("solidDetector", 0.*m, targetRadius, 0.001*m, 0., 360.0*deg);
    logicDetector = new G4LogicalVolume(solidDetector, detectorMaterial, "logicDetector");
    G4VPhysicalVolume* physDetector = new G4PVPlacement(0, detectorPosition, logicDetector, "logicDetector", logicWorld, false, 0, checkOverlaps);


    //                                        
    // Visualization attributes

    logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

    G4VisAttributes* graphiteVisAttr= new G4VisAttributes(G4Colour::Blue());
    graphiteVisAttr->SetVisibility(true);
    graphiteVisAttr->SetForceSolid(true);

    for (G4LogicalVolume* lv : graphiteLogicalVolumes) {
        lv->SetVisAttributes(graphiteVisAttr);
    }

    G4VisAttributes* tantalumVisAttr = new G4VisAttributes(G4Colour::Magenta());
    tantalumVisAttr->SetVisibility(true);
    tantalumVisAttr->SetForceSolid(true);

    for (G4LogicalVolume* lv : tantalumLogicalVolumes) {
        lv->SetVisAttributes(tantalumVisAttr);
    }


    G4VisAttributes* detectorVisAtt= new G4VisAttributes(G4Colour::White());
    detectorVisAtt->SetVisibility(true);
    detectorVisAtt->SetForceWireframe(true);
    logicDetector->SetVisAttributes(detectorVisAtt);


    return physWorld;
}
