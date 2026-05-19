#include "telemetry_logger.h"

TelemetryLogger::TelemetryLogger(const std::string& filename) {
    file.open(filename);

    file << "time,mode,battery_percent,battery_voltage,temperature_c,heater,faults\n";
}

TelemetryLogger::~TelemetryLogger() {
    if (file.is_open()) {
        file.close();
    }
}

void TelemetryLogger::writePacket(const TelemetryPacket& packet) {
    file << packet.timeSeconds << ","
         << packet.mode << ","
         << packet.batteryPercent << ","
         << packet.batteryVoltage << ","
         << packet.temperatureC << ","
         << (packet.heaterOn ? "ON" : "OFF") << ","
         << packet.faults << "\n";
}