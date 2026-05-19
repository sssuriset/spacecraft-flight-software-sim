#include <iostream>
#include <vector>
#include <string>

#include "power.h"
#include "thermal.h"
#include "comms.h"
#include "fault_manager.h"
#include "scheduler.h"

int main() {
    Power power;
    Thermal thermal;
    Comms comms;
    FaultManager faultManager;
    Scheduler scheduler;

    bool safeMode = false;

    std::vector<std::string> commandQueue = {
        "REQUEST_TELEMETRY",
        "SET_HEATER_ON",
        "REQUEST_TELEMETRY",
        "SET_HEATER_OFF",
        "BAD_COMMAND",
        "ENTER_SAFE_MODE"
    };

    int commandIndex = 0;

    std::cout << "Spacecraft flight software simulator starting..." << std::endl;

    for (int t = 0; t <= 30; t++) {
        bool inSunlight = t < 15;

        if (scheduler.shouldRun(t, 1)) {
            power.update(8.0);
            thermal.update(inSunlight);

            faultManager.checkFaults(power.getBatteryPercent(), thermal.getTemperatureC());

            if (faultManager.hasFault()) {
                safeMode = true;
                thermal.setHeater(false);

                std::cout << "[t=" << t << "s] FAULT DETECTED: "
                          << faultManager.getFaultSummary()
                          << std::endl;
            }
        }

        if (scheduler.shouldRun(t, 2) && commandIndex < commandQueue.size()) {
            std::string commandText = commandQueue[commandIndex];
            Command command = comms.parseCommand(commandText);
            commandIndex++;

            std::cout << "[t=" << t << "s] COMMAND RECEIVED: "
                      << commandText
                      << std::endl;

            if (command == Command::SetHeaterOn) {
                thermal.setHeater(true);
                std::cout << "[t=" << t << "s] HEATER STATE: ON" << std::endl;
            } else if (command == Command::SetHeaterOff) {
                thermal.setHeater(false);
                std::cout << "[t=" << t << "s] HEATER STATE: OFF" << std::endl;
            } else if (command == Command::RequestTelemetry) {
                std::cout << "[t=" << t << "s] TELEMETRY: "
                          << "battery=" << power.getBatteryPercent() << "%, "
                          << "voltage=" << power.getBatteryVoltage() << " V, "
                          << "temp=" << thermal.getTemperatureC() << " C, "
                          << "heater=" << (thermal.isHeaterOn() ? "ON" : "OFF")
                          << std::endl;
            } else if (command == Command::EnterSafeMode) {
                safeMode = true;
                thermal.setHeater(false);
                std::cout << "[t=" << t << "s] SYSTEM MODE: SAFE" << std::endl;
            } else if (command == Command::Invalid) {
                std::cout << "[t=" << t << "s] ERROR: invalid command rejected" << std::endl;
            }
        }

        if (scheduler.shouldRun(t, 5)) {
            std::cout << "[t=" << t << "s] STATE: "
                      << "mode=" << (safeMode ? "SAFE" : "NOMINAL") << ", "
                      << "battery=" << power.getBatteryPercent() << "%, "
                      << "voltage=" << power.getBatteryVoltage() << " V, "
                      << "temp=" << thermal.getTemperatureC() << " C, "
                      << "heater=" << (thermal.isHeaterOn() ? "ON" : "OFF") << ", "
                      << "faults=" << faultManager.getFaultSummary()
                      << std::endl;
        }
    }

    return 0;
}