#include "power.h"

Power::Power() {
    batteryPercent = 85.0;
    batteryVoltage = 28.0;
    solarCharging = true;
}

void Power::update(double loadWatts) {
    if (solarCharging) {
        batteryPercent += 0.05;
    }

    batteryPercent -= loadWatts * 0.01;

    if (batteryPercent > 100.0) {
        batteryPercent = 100.0;
    }

    if (batteryPercent < 0.0) {
        batteryPercent = 0.0;
    }

    batteryVoltage = 22.0 + (batteryPercent / 100.0) * 8.0;
}

double Power::getBatteryPercent() const {
    return batteryPercent;
}

double Power::getBatteryVoltage() const {
    return batteryVoltage;
}

bool Power::isSolarCharging() const {
    return solarCharging;
}