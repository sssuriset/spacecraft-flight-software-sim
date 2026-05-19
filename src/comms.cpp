#include "comms.h"

Command Comms::parseCommand(const std::string& commandText) const {
    if (commandText == "NO_OP") {
        return Command::NoOp;
    }

    if (commandText == "SET_HEATER_ON") {
        return Command::SetHeaterOn;
    }

    if (commandText == "SET_HEATER_OFF") {
        return Command::SetHeaterOff;
    }

    if (commandText == "REQUEST_TELEMETRY") {
        return Command::RequestTelemetry;
    }

    if (commandText == "ENTER_SAFE_MODE") {
        return Command::EnterSafeMode;
    }

    return Command::Invalid;
}

std::string Comms::commandToString(Command command) const {
    switch (command) {
        case Command::NoOp:
            return "NO_OP";
        case Command::SetHeaterOn:
            return "SET_HEATER_ON";
        case Command::SetHeaterOff:
            return "SET_HEATER_OFF";
        case Command::RequestTelemetry:
            return "REQUEST_TELEMETRY";
        case Command::EnterSafeMode:
            return "ENTER_SAFE_MODE";
        default:
            return "INVALID";
    }
}