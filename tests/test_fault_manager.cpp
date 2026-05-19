#include <cassert>
#include <iostream>
#include "fault_manager.h"

int main() {
    FaultManager faults;

    faults.checkFaults(85.0, 20.0);
    assert(faults.hasFault() == false);
    assert(faults.getFaultSummary() == "NONE");

    faults.checkFaults(10.0, 20.0);
    assert(faults.hasFault() == true);
    assert(faults.hasLowBatteryFault() == true);

    faults.checkFaults(85.0, 50.0);
    assert(faults.hasFault() == true);
    assert(faults.hasHighTemperatureFault() == true);

    faults.checkFaults(85.0, -10.0);
    assert(faults.hasFault() == true);
    assert(faults.hasLowTemperatureFault() == true);

    std::cout << "Fault manager tests passed." << std::endl;

    return 0;
}