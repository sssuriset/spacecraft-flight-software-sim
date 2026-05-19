#ifndef TELEMETRY_LOGGER_H
#define TELEMETRY_LOGGER_H

#include <fstream>
#include <string>
#include "telemetry.h"

class TelemetryLogger {
private:
    std::ofstream file;

public:
    TelemetryLogger(const std::string& filename);
    ~TelemetryLogger();

    void writePacket(const TelemetryPacket& packet);
};

#endif