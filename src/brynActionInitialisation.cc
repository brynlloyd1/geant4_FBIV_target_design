#include "brynActionInitialisation.hh"
#include "brynPrimaryActionGenerator.hh"
#include "brynSteppingAction.hh"

void brynActionInitialisation::Build() const {
    SetUserAction(new brynPrimaryGeneratorAction);
    SetUserAction(new brynSteppingAction);
}
