#include "brynTrackInformation.hh"

brynTrackInformation::brynTrackInformation() : parentProcess("unknown"), grandParentProcess("unknown") {}
brynTrackInformation::brynTrackInformation(const brynTrackInformation* info) : parentProcess(info->parentProcess), grandParentProcess(info->grandParentProcess) {}
