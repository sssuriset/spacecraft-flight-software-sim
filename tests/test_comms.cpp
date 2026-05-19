#include <cassert>
#include <iostream>
#include "comms.h"

int main() {
    Comms comms;

    assert(comms.parseCommand("NO_OP") == Command::NoOp);
    assert(comms.parseCommand("SET_HEATER_ON") == Command::SetHeaterOn);
    assert(comms.parseCommand("SET_HEATER_OFF") == Command::SetHeaterOff);
    assert(comms.parseCommand("REQUEST_TELEMETRY") == Command::RequestTelemetry);
    assert(comms.parseCommand("ENTER_SAFE_MODE") == Command::EnterSafeMode);
    assert(comms.parseCommand("BAD_COMMAND") == Command::Invalid);

    assert(comms.commandToString(Command::NoOp) == "NO_OP");
    assert(comms.commandToString(Command::SetHeaterOn) == "SET_HEATER_ON");
    assert(comms.commandToString(Command::Invalid) == "INVALID");

    std::cout << "Comms tests passed." << std::endl;

    return 0;
}