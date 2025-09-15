// geant4 imports
#include "G4RunManagerFactory.hh"
#include "G4RunManager.hh"
#include "G4UIManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4VisManager.hh"
#include "FTFP_BERT.hh"

// bryn imports
#include "brynDetectorConstruction_FBII.hh"
#include "brynDetectorConstruction_FBIII.hh"
#include "brynDetectorConstruction_TESTING.hh"
#include "brynDetectorConstruction_COREHOLE.hh"
#include "brynActionInitialisation.hh"
#include <G4ios.hh>



int main(int argc, char** argv) {

    // validate CLI input
    if (argc < 2) {
        G4cerr << "Usage: " << argv[0] << "<detector_setup> [macro_file]" << G4endl;
        return 1;
    }

    // parse CLI input
    std::string detectorConfiguration = argv[1];
    std::string macroFile = (argc >= 3) ? argv[2] : "";

    ///////////////////////
    // run manager setup //
    ///////////////////////
    auto* runManager = G4RunManagerFactory::CreateRunManager();

    if (detectorConfiguration == "FBII") {
        runManager->SetUserInitialization(new brynDetectorConstruction_FBII);
    } else if (detectorConfiguration == "FBIII") {
        runManager->SetUserInitialization(new brynDetectorConstruction_FBIII);
    } else if (detectorConfiguration == "TESTING") {
        runManager->SetUserInitialization(new brynDetectorConstruction_TESTING);
    } else if (detectorConfiguration == "COREHOLE") {
        runManager->SetUserInitialization(new brynDetectorConstruction_COREHOLE);
    } else {
        G4cerr << "Unknown detector setup: " << detectorConfiguration << G4endl;
    }

    runManager->SetUserInitialization(new FTFP_BERT);
    runManager->SetUserInitialization(new brynActionInitialisation);
    runManager->Initialize();

    ///////////////////////
    // vis manager setup //
    ///////////////////////
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    G4UIExecutive* ui = nullptr;
    if (argc < 3) {
        ui = new G4UIExecutive(argc, argv);
    }


    // Get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();  

    if (ui) {
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    } else { 
        G4String command = "/control/execute ";
        G4String fileName = macroFile;
        UImanager->ApplyCommand(command+fileName);
    }





    /////////////
    // cleanup //
    /////////////
    delete runManager;
    delete visManager;
}
