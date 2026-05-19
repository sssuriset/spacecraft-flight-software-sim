#ifndef COMMS_H
#define COMMS_H

#include <string>

enum class Command {
    NoOp,
    SetHeaterOn,
    SetHeaterOff,
    RequestTelemetry,
    EnterSafeMode,
    Invalid
};

class Comms {
public:
    Command parseCommand(const std::string& commandText) const;
    std::string commandToString(Command command) const;
};

#endif