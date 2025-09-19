#include "brynSteppingAction.hh"
#include "brynTrackInformation.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"



void brynSteppingAction::UserSteppingAction(const G4Step* step) {
    G4Track* track = step->GetTrack();

    if (track->GetParentID() == 0 && !track->GetUserInformation()) {
        brynTrackInformation* info = new brynTrackInformation();
        info->AddToAncestry("primary");
        track->SetUserInformation(info);
    }

    auto* parentInfo = dynamic_cast<brynTrackInformation*>(track->GetUserInformation());
    if (!parentInfo) return;

    const auto* secondaries = step->GetSecondaryInCurrentStep();
    if (!secondaries) return;

    for (auto* secondary : *secondaries) {
        if (!secondary->GetUserInformation()) {
            brynTrackInformation* secondaryInfo = new brynTrackInformation();

            secondaryInfo->SetAncestry(parentInfo->GetAncestry());

            G4String parentProcess = "unknown";
            if (secondary->GetCreatorProcess()) {
                parentProcess = secondary->GetCreatorProcess()->GetProcessName();
            }
            secondaryInfo->AddToAncestry(parentProcess);
            secondary->SetUserInformation(secondaryInfo);
        }
    }
}
