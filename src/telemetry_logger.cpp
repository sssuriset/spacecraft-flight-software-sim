#include "telemetry_logger.h"
#include <stdexcept>

TelemetryLogger::TelemetryLogger(const std::string& filename) {
    file.open(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open telemetry log file: " + filename);
    }

    file << "time,mode,battery_percent,battery_voltage,temperature_c,heater,faults\n";
}

TelemetryLogger::~TelemetryLogger() {
    if (file.is_open()) {
        file.close();
    }
}

void TelemetryLogger::writePacket(const TelemetryPacket& packet) {
    if (!file.is_open()) {
        throw std::runtime_error("Telemetry log file is not open");
    }

    file << packet.timeSeconds << ","
         << packet.mode << ","
         << packet.batteryPercent << ","
         << packet.batteryVoltage << ","
         << packet.temperatureC << ","
         << (packet.heaterOn ? "ON" : "OFF") << ","
         << packet.faults << "\n";
}
