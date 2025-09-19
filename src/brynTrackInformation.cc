#include "brynTrackInformation.hh"
#include <G4VUserTrackInformation.hh>

brynTrackInformation::brynTrackInformation() : G4VUserTrackInformation() {}
brynTrackInformation::brynTrackInformation(const brynTrackInformation* info) : G4VUserTrackInformation() {
    ancestry = info->GetAncestry();
}
