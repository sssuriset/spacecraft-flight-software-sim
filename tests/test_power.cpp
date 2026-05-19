#include <cassert>
#include <iostream>
#include "power.h"

int main() {
    Power power;

    double startBattery = power.getBatteryPercent();

    power.update(8.0);

    assert(power.getBatteryPercent() < startBattery);
    assert(power.getBatteryVoltage() > 0.0);
    assert(power.getBatteryPercent() >= 0.0);
    assert(power.getBatteryPercent() <= 100.0);

    std::cout << "Power tests passed." << std::endl;

    return 0;
}