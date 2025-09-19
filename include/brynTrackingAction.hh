#ifndef brynTrackingAction_hh
#define brynTrackingAction_hh

#include "G4UserTrackingAction.hh"

class brynTrackingAction : public G4UserTrackingAction {
public:
    brynTrackingAction() {}
    virtual ~brynTrackingAction() {}

    virtual void PreUserTrackingAction(const G4Track*);
    virtual void PostUserTrackingAction(const G4Track*) {}
};

#endif
