#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include <string>
#include "power.h"
#include "thermal.h"
#include "comms.h"
#include "fault_manager.h"
#include "mode.h"
#include "telemetry.h"

class Spacecraft {
private:
    Power power;
    Thermal thermal;
    Comms comms;
    FaultManager faultManager;
    SpacecraftMode mode;
    bool immediateTelemetryRequested;

    bool isProtectiveMode() const;
    void applyProtectiveModeActions();

public:
    Spacecraft();

    void boot();
    void updateEnvironment(bool inSunlight);
    std::string processCommand(const std::string& commandText);

    TelemetryPacket buildTelemetryPacket(int timeSeconds) const;
    bool consumeImmediateTelemetryRequest();

    SpacecraftMode getMode() const;
    double getBatteryPercent() const;
    double getBatteryVoltage() const;
    double getTemperatureC() const;
    bool isHeaterOn() const;
    std::string getFaultSummary() const;
};

#endif
