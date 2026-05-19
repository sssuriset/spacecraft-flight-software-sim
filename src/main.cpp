#include <iostream>
#include <vector>
#include <string>

#include "power.h"
#include "thermal.h"
#include "comms.h"
#include "fault_manager.h"

int main() {
    Power power;
    Thermal thermal;
    Comms comms;
    FaultManager faultManager;

    bool safeMode = false;

    std::vector<std::string> commandQueue = {
        "REQUEST_TELEMETRY",
        "SET_HEATER_ON",
        "REQUEST_TELEMETRY",
        "SET_HEATER_OFF",
        "BAD_COMMAND",
        "ENTER_SAFE_MODE"
    };

    std::cout << "Spacecraft flight software simulator starting..." << std::endl;

    for (int t = 0; t <= 20; t++) {
        bool inSunlight = t < 10;

        power.update(8.0);
        thermal.update(inSunlight);

        faultManager.checkFaults(power.getBatteryPercent(), thermal.getTemperatureC());

        if (faultManager.hasFault()) {
            safeMode = true;
            thermal.setHeater(false);

            std::cout << "[t=" << t << "s] FAULT DETECTED: "
                      << faultManager.getFaultSummary()
                      << std::endl;

            std::cout << "[t=" << t << "s] SYSTEM MODE: SAFE" << std::endl;
        }

        if (t < commandQueue.size()) {
            std::string commandText = commandQueue[t];
            Command command = comms.parseCommand(commandText);

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

        std::cout << "[t=" << t << "s] STATE: "
                  << "mode=" << (safeMode ? "SAFE" : "NOMINAL") << ", "
                  << "battery=" << power.getBatteryPercent() << "%, "
                  << "voltage=" << power.getBatteryVoltage() << " V, "
                  << "temp=" << thermal.getTemperatureC() << " C, "
                  << "heater=" << (thermal.isHeaterOn() ? "ON" : "OFF") << ", "
                  << "faults=" << faultManager.getFaultSummary()
                  << std::endl;
    }

    return 0;
}