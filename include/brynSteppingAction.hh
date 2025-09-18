#ifndef brynSteppingAction_hh
#define brynSteppingAction_hh

#include "G4UserSteppingAction.hh"

class brynSteppingAction : public G4UserSteppingAction {
public:
    brynSteppingAction() {}
    virtual ~brynSteppingAction() {}

    virtual void UserSteppingAction(const G4Step* step) override;
};
#endif
