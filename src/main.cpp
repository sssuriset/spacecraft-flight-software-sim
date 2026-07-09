#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "scheduler.h"
#include "spacecraft.h"
#include "telemetry.h"
#include "telemetry_logger.h"

struct TimedCommand {
    int timeSeconds;
    std::string text;
};

static std::vector<TimedCommand> loadCommandSequence(const std::string& path) {
    std::vector<TimedCommand> sequence;
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "WARNING: could not open command file '" << path
                  << "', running with no command sequence" << std::endl;
        return sequence;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream stream(line);
        TimedCommand command;

        if (stream >> command.timeSeconds >> command.text) {
            sequence.push_back(command);
        } else {
            std::cerr << "WARNING: skipping malformed command line: "
                      << line << std::endl;
        }
    }

    return sequence;
}

static void printTelemetry(const TelemetryPacket& packet) {
    std::cout << "[t=" << packet.timeSeconds << "s] STATE: "
              << "mode=" << packet.mode << ", "
              << "battery=" << packet.batteryPercent << "%, "
              << "voltage=" << packet.batteryVoltage << " V, "
              << "temp=" << packet.temperatureC << " C, "
              << "heater=" << (packet.heaterOn ? "ON" : "OFF") << ", "
              << "faults=" << packet.faults << std::endl;
}

int main(int argc, char* argv[]) {
    Spacecraft spacecraft;
    Scheduler scheduler;
    TelemetryLogger telemetryLogger("telemetry_log.csv");

    scheduler.registerTask("environment_update", 1, 1);
    scheduler.registerTask("telemetry_logging", 5, 3);

    std::string commandFilePath = argc > 1 ? argv[1] : "commands.txt";
    std::vector<TimedCommand> commandSequence = loadCommandSequence(commandFilePath);
    size_t commandIndex = 0;

    std::cout << "Spacecraft flight software simulator starting..." << std::endl;
    std::cout << "Loaded " << commandSequence.size()
              << " commands from " << commandFilePath << std::endl;

    spacecraft.boot();

    for (int t = 0; t <= 30; t++) {
        bool inSunlight = t < 15;

        if (scheduler.shouldRunTask("environment_update", t)) {
            spacecraft.updateEnvironment(inSunlight);

            if (spacecraft.getMode() == SpacecraftMode::Fault) {
                std::cout << "[t=" << t << "s] FAULT DETECTED: "
                          << spacecraft.getFaultSummary() << std::endl;
            }
        }

        while (commandIndex < commandSequence.size() &&
               commandSequence[commandIndex].timeSeconds <= t) {
            const std::string& commandText = commandSequence[commandIndex].text;
            commandIndex++;

            std::cout << "[t=" << t << "s] COMMAND RECEIVED: "
                      << commandText << std::endl;

            std::string result = spacecraft.processCommand(commandText);
            std::cout << "[t=" << t << "s] " << result << std::endl;
        }

        if (spacecraft.consumeImmediateTelemetryRequest()) {
            TelemetryPacket packet = spacecraft.buildTelemetryPacket(t);
            telemetryLogger.writePacket(packet);
            std::cout << "[t=" << t << "s] IMMEDIATE TELEMETRY" << std::endl;
            printTelemetry(packet);
        }

        if (scheduler.shouldRunTask("telemetry_logging", t)) {
            TelemetryPacket packet = spacecraft.buildTelemetryPacket(t);
            telemetryLogger.writePacket(packet);
            printTelemetry(packet);
        }
    }

    return 0;
}
