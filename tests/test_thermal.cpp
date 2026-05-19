#include <cassert>
#include <iostream>
#include "thermal.h"

int main() {
    Thermal thermal;

    double startTemp = thermal.getTemperatureC();

    thermal.update(true);
    assert(thermal.getTemperatureC() > startTemp);

    double sunlightTemp = thermal.getTemperatureC();

    thermal.update(false);
    assert(thermal.getTemperatureC() < sunlightTemp);

    thermal.setHeater(true);
    assert(thermal.isHeaterOn() == true);

    double heaterStartTemp = thermal.getTemperatureC();
    thermal.update(false);
    assert(thermal.getTemperatureC() > heaterStartTemp);

    thermal.setHeater(false);
    assert(thermal.isHeaterOn() == false);

    std::cout << "Thermal tests passed." << std::endl;

    return 0;
}