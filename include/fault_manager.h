#ifndef FAULT_MANAGER_H
#define FAULT_MANAGER_H

#include <string>

class FaultManager {
private:
    bool lowBatteryFault;
    bool highTemperatureFault;
    bool lowTemperatureFault;

public:
    FaultManager();

    void checkFaults(double batteryPercent, double temperatureC);

    bool hasFault() const;
    bool hasLowBatteryFault() const;
    bool hasHighTemperatureFault() const;
    bool hasLowTemperatureFault() const;

    std::string getFaultSummary() const;
};

#endif