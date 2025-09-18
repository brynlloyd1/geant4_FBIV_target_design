#include "brynTrackingAction.hh"
#include "brynTrackInformation.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"

void brynTrackingAction::PreUserTrackingAction(const G4Track* track) {
    G4String creatorProc = "primary";
    const G4VProcess* creator = track->GetCreatorProcess();
    if (creator) {
        creatorProc = creator->GetProcessName();
    }

    brynTrackInformation* info = new brynTrackInformation(creatorProc);

    G4Track* nonConstTrack = const_cast<G4Track*>(track);
    nonConstTrack->SetUserInformation(info);
}
