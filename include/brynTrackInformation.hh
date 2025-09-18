#ifndef brynTrackInformation_hh
#define brynTrackInformation_hh

#include "G4VUserTrackInformation.hh"

class brynTrackInformation : public G4VUserTrackInformation {
public:

    brynTrackInformation();
    brynTrackInformation(const brynTrackInformation* info);
    virtual ~brynTrackInformation() {}

    void SetParentProcess(G4String proc) { parentProcess = proc; }
    G4String GetParentProcess() const { return parentProcess; }

    void SetGrandParentProcess(G4String name) { grandParentProcess = name; }
    G4String GetGrandParentProcess() const { return grandParentProcess; }

private:
    G4String parentProcess;
    G4String grandParentProcess;
};


#endif
