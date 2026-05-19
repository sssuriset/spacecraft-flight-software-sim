#include <iostream>
#include "power.h"
#include "thermal.h"

int main() {
    Power power;
    Thermal thermal;

    std::cout << "Spacecraft flight software simulator starting..." << std::endl;

    for (int time = 0; time <= 20; time++) {
        bool inSunlight = time < 10;

        power.update(8.0);
        thermal.update(inSunlight);

        if (thermal.getTemperatureC() < 18.0) {
            thermal.setHeater(true);
        }

        if (thermal.getTemperatureC() > 22.0) {
            thermal.setHeater(false);
        }

        std::cout << "[t=" << time << "s] "
                  << "battery=" << power.getBatteryPercent() << "%, "
                  << "voltage=" << power.getBatteryVoltage() << " V, "
                  << "temp=" << thermal.getTemperatureC() << " C, "
                  << "heater=" << (thermal.isHeaterOn() ? "ON" : "OFF")
                  << std::endl;
    }

    return 0;
}