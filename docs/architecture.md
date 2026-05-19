# Architecture

This project is organized as a small spacecraft flight software simulator. The simulator is separated into subsystem modules so each component has a clear responsibility.

## Main Control Loop

`main.cpp` runs the simulation loop. Each loop iteration represents one second of simulated spacecraft time.

The main loop is responsible for:

- Updating subsystem state
- Running scheduled tasks
- Processing commands from `commands.txt`
- Checking faults
- Writing telemetry packets
- Printing state updates to the terminal

## Scheduler

The scheduler controls when tasks run.

Current task timing:

```text
Power update: every 1 second
Thermal update: every 1 second
Fault check: every 1 second
Command processing: based on commands.txt timestamps
Telemetry logging: every 5 seconds