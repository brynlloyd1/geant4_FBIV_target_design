#include "brynActionInitialisation.hh"
#include "brynPrimaryActionGenerator.hh"
#include "brynTrackingAction.hh"

void brynActionInitialisation::Build() const {
    SetUserAction(new brynPrimaryGeneratorAction);
    SetUserAction(new brynTrackingAction);
}
