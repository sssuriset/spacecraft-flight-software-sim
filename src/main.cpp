#include <iostream>
#include "power.h"

int main() {
    Power power;

    std::cout << "Spacecraft flight software simulator starting..." << std::endl;

    for (int time = 0; time <= 10; time++) {
        power.update(5.0);

        std::cout << "[t=" << time << "s] "
                  << "battery=" << power.getBatteryPercent() << "%, "
                  << "voltage=" << power.getBatteryVoltage() << " V"
                  << std::endl;
    }

    return 0;
}