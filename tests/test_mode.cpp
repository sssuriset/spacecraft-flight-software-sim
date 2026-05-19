#include <cassert>
#include <iostream>
#include "mode.h"

int main() {
    assert(modeToString(SpacecraftMode::Boot) == "BOOT");
    assert(modeToString(SpacecraftMode::Nominal) == "NOMINAL");
    assert(modeToString(SpacecraftMode::Safe) == "SAFE");
    assert(modeToString(SpacecraftMode::Fault) == "FAULT");

    std::cout << "Mode tests passed." << std::endl;

    return 0;
}