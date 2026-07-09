# Spacecraft Flight Software Simulator

[![CI](https://github.com/sssuriset/spacecraft-flight-software-sim/actions/workflows/ci.yml/badge.svg)](https://github.com/sssuriset/spacecraft-flight-software-sim/actions/workflows/ci.yml)

A C++17 simulator for the software side of a small spacecraft: subsystem state, a periodic task scheduler, timestamped command processing, fault detection with protective modes, and CSV telemetry logging. Each loop iteration represents one second of spacecraft time over a 30 second scenario that includes an eclipse entry at t=15s.

## Build and run

```bash
cmake -B build
cmake --build build
./build/spacecraft_sim
```

Run the unit tests:

```bash
ctest --test-dir build
```

The simulator reads `commands.txt` from the working directory by default. A different command file can be passed as the first argument:

```bash
./build/spacecraft_sim my_sequence.txt
```

## Command sequences

Commands are loaded from a text file with one timestamped command per line:

```text
# <time_seconds> <command>
0 REQUEST_TELEMETRY
2 SET_HEATER_ON
10 ENTER_SAFE_MODE
12 SET_HEATER_ON
```

Blank lines and lines starting with `#` are skipped. Malformed lines are reported and skipped rather than aborting the run. Each command dispatches when simulation time reaches its timestamp.

Supported commands:

| Command | Effect |
|---|---|
| `REQUEST_TELEMETRY` | Emits an immediate telemetry packet outside the periodic schedule |
| `SET_HEATER_ON` / `SET_HEATER_OFF` | Controls the thermal subsystem heater |
| `ENTER_SAFE_MODE` | Transitions to SAFE mode |
| `NO_OP` | Accepted with no state change |

Unrecognized commands are rejected with an error, and the run continues.

## Subsystems

| Module | Responsibility |
|---|---|
| `power` | Battery percent and voltage, solar charging when in sunlight, load draw |
| `thermal` | Temperature model driven by sunlight state, heater control |
| `comms` | Command string parsing into a typed command enum |
| `fault_manager` | Threshold checks: battery < 20%, temperature > 45 C or < -5 C |
| `scheduler` | Named periodic tasks with per-task periods and priorities |
| `telemetry_logger` | Writes each telemetry packet as a CSV row to `telemetry_log.csv` |
| `spacecraft` | Owns the subsystems, mode state machine, and command handling |

## Modes and fault handling

The mode state machine is BOOT -> NOMINAL, with transitions into SAFE (commanded) or FAULT (detected). SAFE and FAULT are protective modes. In a protective mode the spacecraft:

- rejects actuator commands such as `SET_HEATER_ON`, while still accepting `REQUEST_TELEMETRY` and `NO_OP`
- drops its power load from 8 W to 3 W
- runs a survival heater rule, heater on below 0 C
- emits an immediate telemetry packet on the transition

Fault detection runs every environment update. A threshold violation latches FAULT mode and prints the active fault summary.

## Telemetry

Telemetry packets carry time, mode, battery percent, battery voltage, temperature, heater state, and the fault summary. Packets are logged on a 5 second schedule and immediately on telemetry requests and protective mode transitions, then written to `telemetry_log.csv`.

## Tests

Each subsystem has a standalone assertion test registered with CTest: `test_power`, `test_scheduler`, `test_fault_manager`, `test_comms`, `test_thermal`, `test_mode`. CI builds the project and runs the test suite plus a full simulation with the checked-in command sequence on every push.

## Layout

```text
include/   subsystem headers
src/       subsystem implementations and main loop
tests/     per-subsystem assertion tests
commands.txt   default command sequence
```
