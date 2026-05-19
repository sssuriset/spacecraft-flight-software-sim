#include <iostream>
#include <vector>
#include <string>

#include "power.h"
#include "thermal.h"
#include "comms.h"

int main() {
    Power power;
    Thermal thermal;
    Comms comms;

    std::vector<std::string> commandQueue = {
        "REQUEST_TELEMETRY",
        "SET_HEATER_ON",
        "REQUEST_TELEMETRY",
        "SET_HEATER_OFF",
        "BAD_COMMAND",
        "ENTER_SAFE_MODE"
    };

    std::cout << "Spacecraft flight software simulator starting..." << std::endl;

    for (int time = 0; time <= 20; time++) {
        bool inSunlight = time < 10;

        power.update(8.0);
        thermal.update(inSunlight);

        if (time < commandQueue.size()) {
            std::string commandText = commandQueue[time];
            Command command = comms.parseCommand(commandText);

            std::cout << "[t=" << time << "s] "
                      << "COMMAND RECEIVED: "
                      << commandText
                      << std::endl;

            if (command == Command::SetHeaterOn) {
                thermal.setHeater(true);
                std::cout << "[t=" << time << "s] HEATER STATE: ON" << std::endl;
            } else if (command == Command::SetHeaterOff) {
                thermal.setHeater(false);
                std::cout << "[t=" << time << "s] HEATER STATE: OFF" << std::endl;
            } else if (command == Command::RequestTelemetry) {
                std::cout << "[t=" << time << "s] TELEMETRY: "
                          << "battery=" << power.getBatteryPercent() << "%, "
                          << "voltage=" << power.getBatteryVoltage() << " V, "
                          << "temp=" << thermal.getTemperatureC() << " C, "
                          << "heater=" << (thermal.isHeaterOn() ? "ON" : "OFF")
                          << std::endl;
            } else if (command == Command::EnterSafeMode) {
                thermal.setHeater(false);
                std::cout << "[t=" << time << "s] SYSTEM MODE: SAFE" << std::endl;
            } else if (command == Command::Invalid) {
                std::cout << "[t=" << time << "s] ERROR: invalid command rejected" << std::endl;
            }
        }

        std::cout << "[t=" << time << "s] STATE: "
                  << "battery=" << power.getBatteryPercent() << "%, "
                  << "voltage=" << power.getBatteryVoltage() << " V, "
                  << "temp=" << thermal.getTemperatureC() << " C, "
                  << "heater=" << (thermal.isHeaterOn() ? "ON" : "OFF")
                  << std::endl;
    }

    return 0;
}