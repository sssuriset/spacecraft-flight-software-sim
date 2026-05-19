#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <string>

struct TelemetryPacket {
    int timeSeconds;
    std::string mode;
    double batteryPercent;
    double batteryVoltage;
    double temperatureC;
    bool heaterOn;
    std::string faults;
};

#endif