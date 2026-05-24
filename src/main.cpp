#include <iostream>
#include <string>
#include <vector>

#include "scheduler.h"
#include "spacecraft.h"
#include "telemetry.h"
#include "telemetry_logger.h"

static void printTelemetry(const TelemetryPacket& packet) {
    std::cout << "[t=" << packet.timeSeconds << "s] STATE: "
              << "mode=" << packet.mode << ", "
              << "battery=" << packet.batteryPercent << "%, "
              << "voltage=" << packet.batteryVoltage << " V, "
              << "temp=" << packet.temperatureC << " C, "
              << "heater=" << (packet.heaterOn ? "ON" : "OFF") << ", "
              << "faults=" << packet.faults << std::endl;
}

int main() {
    Spacecraft spacecraft;
    Scheduler scheduler;
    TelemetryLogger telemetryLogger("telemetry_log.csv");

    scheduler.registerTask("environment_update", 1, 1);
    scheduler.registerTask("command_processing", 2, 2);
    scheduler.registerTask("telemetry_logging", 5, 3);

    std::vector<std::string> commandQueue = {
        "REQUEST_TELEMETRY",
        "SET_HEATER_ON",
        "REQUEST_TELEMETRY",
        "SET_HEATER_OFF",
        "BAD_COMMAND",
        "ENTER_SAFE_MODE",
        "SET_HEATER_ON",
        "REQUEST_TELEMETRY"
    };

    int commandIndex = 0;

    std::cout << "Spacecraft flight software simulator starting..." << std::endl;

    spacecraft.boot();

    for (int t = 0; t <= 30; t++) {
        bool inSunlight = t < 15;

        if (scheduler.shouldRunTask("environment_update", t)) {
            spacecraft.updateEnvironment(inSunlight);

            if (spacecraft.getMode() == SpacecraftMode::Fault) {
                std::cout << "[t=" << t << "s] FAULT DETECTED: "
                          << spacecraft.getFaultSummary() << std::endl;
            }
        }

        if (scheduler.shouldRunTask("command_processing", t) &&
            commandIndex < static_cast<int>(commandQueue.size())) {
            std::string commandText = commandQueue[commandIndex];
            commandIndex++;

            std::cout << "[t=" << t << "s] COMMAND RECEIVED: "
                      << commandText << std::endl;

            std::string result = spacecraft.processCommand(commandText);
            std::cout << "[t=" << t << "s] " << result << std::endl;
        }

        if (spacecraft.consumeImmediateTelemetryRequest()) {
            TelemetryPacket packet = spacecraft.buildTelemetryPacket(t);
            telemetryLogger.writePacket(packet);
            std::cout << "[t=" << t << "s] IMMEDIATE TELEMETRY" << std::endl;
            printTelemetry(packet);
        }

        if (scheduler.shouldRunTask("telemetry_logging", t)) {
            TelemetryPacket packet = spacecraft.buildTelemetryPacket(t);
            telemetryLogger.writePacket(packet);
            printTelemetry(packet);
        }
    }

    return 0;
}
