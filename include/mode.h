#ifndef MODE_H
#define MODE_H

#include <string>

enum class SpacecraftMode {
    Boot,
    Nominal,
    Safe,
    Fault
};

inline std::string modeToString(SpacecraftMode mode) {
    switch (mode) {
        case SpacecraftMode::Boot:
            return "BOOT";
        case SpacecraftMode::Nominal:
            return "NOMINAL";
        case SpacecraftMode::Safe:
            return "SAFE";
        case SpacecraftMode::Fault:
            return "FAULT";
        default:
            return "UNKNOWN";
    }
}

#endif