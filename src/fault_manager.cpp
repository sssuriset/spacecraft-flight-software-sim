#include "fault_manager.h"

FaultManager::FaultManager() {
    lowBatteryFault = false;
    highTemperatureFault = false;
    lowTemperatureFault = false;
}

void FaultManager::checkFaults(double batteryPercent, double temperatureC) {
    lowBatteryFault = batteryPercent < 20.0;
    highTemperatureFault = temperatureC > 45.0;
    lowTemperatureFault = temperatureC < -5.0;
}

bool FaultManager::hasFault() const {
    return lowBatteryFault || highTemperatureFault || lowTemperatureFault;
}

bool FaultManager::hasLowBatteryFault() const {
    return lowBatteryFault;
}

bool FaultManager::hasHighTemperatureFault() const {
    return highTemperatureFault;
}

bool FaultManager::hasLowTemperatureFault() const {
    return lowTemperatureFault;
}

std::string FaultManager::getFaultSummary() const {
    if (!hasFault()) {
        return "NONE";
    }

    std::string summary = "";

    if (lowBatteryFault) {
        summary += "LOW_BATTERY ";
    }

    if (highTemperatureFault) {
        summary += "HIGH_TEMPERATURE ";
    }

    if (lowTemperatureFault) {
        summary += "LOW_TEMPERATURE ";
    }

    return summary;
}