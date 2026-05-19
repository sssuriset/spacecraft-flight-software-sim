#include "thermal.h"

Thermal::Thermal() {
    temperatureC = 20.0;
    heaterOn = false;
}

void Thermal::update(bool inSunlight) {
    if (inSunlight) {
        temperatureC += 0.15;
    } else {
        temperatureC -= 0.25;
    }

    if (heaterOn) {
        temperatureC += 0.30;
    }
}

void Thermal::setHeater(bool state) {
    heaterOn = state;
}

double Thermal::getTemperatureC() const {
    return temperatureC;
}

bool Thermal::isHeaterOn() const {
    return heaterOn;
}