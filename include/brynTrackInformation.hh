#ifndef brynTrackInformation_hh
#define brynTrackInformation_hh

#include "G4VUserTrackInformation.hh"

class brynTrackInformation : public G4VUserTrackInformation {
public:
    brynTrackInformation() : G4VUserTrackInformation(), creatorProcess("unknown") {}
    brynTrackInformation(const G4String& proc) : creatorProcess(proc) {}
    brynTrackInformation(const brynTrackInformation* info) : G4VUserTrackInformation(), creatorProcess(info->creatorProcess) {}

    virtual ~brynTrackInformation() {}

    void SetCreatorProcess(const G4String& proc) { creatorProcess = proc; }
    G4String GetCreatorProcess() const { return creatorProcess; }

private:
    G4String creatorProcess;
};


#endif
