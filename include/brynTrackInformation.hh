#ifndef brynTrackInformation_hh
#define brynTrackInformation_hh

#include "G4VUserTrackInformation.hh"


class brynTrackInformation : public G4VUserTrackInformation {
public:
    brynTrackInformation();
    brynTrackInformation(const brynTrackInformation* info);
    virtual ~brynTrackInformation() {}

    void AddToAncestry(const G4String& processName) {
        ancestry.push_back(processName);
    }

    const std::vector<G4String>& GetAncestry() const {
        return ancestry;
    }

    void SetAncestry(const std::vector<G4String>& ancestry) {
        this->ancestry = ancestry;
    }

private:
    std::vector<G4String> ancestry;

};
#endif
