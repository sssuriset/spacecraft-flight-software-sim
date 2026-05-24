#include "spacecraft.h"

Spacecraft::Spacecraft() {
    mode = SpacecraftMode::Boot;
    immediateTelemetryRequested = false;
}

void Spacecraft::boot() {
    mode = SpacecraftMode::Nominal;
}

bool Spacecraft::isProtectiveMode() const {
    return mode == SpacecraftMode::Safe || mode == SpacecraftMode::Fault;
}

void Spacecraft::applyProtectiveModeActions() {
    if (thermal.getTemperatureC() < 0.0) {
        thermal.setHeater(true);
    } else {
        thermal.setHeater(false);
    }
}

void Spacecraft::updateEnvironment(bool inSunlight) {
    power.setSolarCharging(inSunlight);

    double loadWatts = 8.0;

    if (isProtectiveMode()) {
        loadWatts = 3.0;
    }

    power.update(loadWatts);
    thermal.update(inSunlight);

    faultManager.checkFaults(power.getBatteryPercent(), thermal.getTemperatureC());

    if (faultManager.hasFault() && mode != SpacecraftMode::Fault) {
        mode = SpacecraftMode::Fault;
        immediateTelemetryRequested = true;
    }

    if (isProtectiveMode()) {
        applyProtectiveModeActions();
    }
}

std::string Spacecraft::processCommand(const std::string& commandText) {
    Command command = comms.parseCommand(commandText);

    if (isProtectiveMode()) {
        if (command == Command::RequestTelemetry) {
            immediateTelemetryRequested = true;
            return "TELEMETRY REQUEST ACCEPTED";
        }

        if (command == Command::NoOp) {
            return "NO_OP ACCEPTED";
        }

        if (command == Command::EnterSafeMode) {
            mode = SpacecraftMode::Safe;
            immediateTelemetryRequested = true;
            applyProtectiveModeActions();
            return "SYSTEM MODE: SAFE";
        }

        if (command == Command::Invalid) {
            return "ERROR: invalid command rejected";
        }

        return "COMMAND REJECTED: spacecraft is in protective mode";
    }

    if (command == Command::SetHeaterOn) {
        thermal.setHeater(true);
        return "HEATER STATE: ON";
    }

    if (command == Command::SetHeaterOff) {
        thermal.setHeater(false);
        return "HEATER STATE: OFF";
    }

    if (command == Command::RequestTelemetry) {
        immediateTelemetryRequested = true;
        return "TELEMETRY REQUEST ACCEPTED";
    }

    if (command == Command::EnterSafeMode) {
        mode = SpacecraftMode::Safe;
        immediateTelemetryRequested = true;
        applyProtectiveModeActions();
        return "SYSTEM MODE: SAFE";
    }

    if (command == Command::NoOp) {
        return "NO_OP ACCEPTED";
    }

    return "ERROR: invalid command rejected";
}

TelemetryPacket Spacecraft::buildTelemetryPacket(int timeSeconds) const {
    TelemetryPacket packet;

    packet.timeSeconds = timeSeconds;
    packet.mode = modeToString(mode);
    packet.batteryPercent = power.getBatteryPercent();
    packet.batteryVoltage = power.getBatteryVoltage();
    packet.temperatureC = thermal.getTemperatureC();
    packet.heaterOn = thermal.isHeaterOn();
    packet.faults = faultManager.getFaultSummary();

    return packet;
}

bool Spacecraft::consumeImmediateTelemetryRequest() {
    if (immediateTelemetryRequested) {
        immediateTelemetryRequested = false;
        return true;
    }

    return false;
}

SpacecraftMode Spacecraft::getMode() const {
    return mode;
}

double Spacecraft::getBatteryPercent() const {
    return power.getBatteryPercent();
}

double Spacecraft::getBatteryVoltage() const {
    return power.getBatteryVoltage();
}

double Spacecraft::getTemperatureC() const {
    return thermal.getTemperatureC();
}

bool Spacecraft::isHeaterOn() const {
    return thermal.isHeaterOn();
}

std::string Spacecraft::getFaultSummary() const {
    return faultManager.getFaultSummary();
}
