# Spacecraft Flight Software Simulator

This project is a C++ simulation of basic spacecraft flight software behavior. It models command handling, telemetry generation, subsystem state updates, periodic task scheduling, fault detection, and safe-mode behavior.

The goal is not to create a high-fidelity spacecraft model. The goal is to practice flight-software-style architecture using C++, Linux terminal workflows, CMake, Git, and basic software testing.

## Features

- Power subsystem simulation
- Thermal subsystem simulation
- Command parsing
- Telemetry output
- Fault detection
- Safe-mode state
- Periodic task scheduler
- Basic subsystem tests using C++ `assert()`

## Simulated Subsystems

### Power

The power subsystem tracks battery percentage and voltage. Battery state changes over time based on simulated load and solar charging.

### Thermal

The thermal subsystem tracks spacecraft temperature and heater state. Temperature changes depending on whether the spacecraft is in sunlight and whether the heater is active.

### Communications

The communications module parses simple ground commands, including:

- `REQUEST_TELEMETRY`
- `SET_HEATER_ON`
- `SET_HEATER_OFF`
- `ENTER_SAFE_MODE`

Invalid commands are rejected.

### Fault Management

The fault manager checks for low battery, high temperature, and low temperature conditions. If a fault is detected, the spacecraft enters safe mode.

### Scheduler

The scheduler controls when tasks run. This simulates a simple real-time task structure where different software tasks execute at fixed intervals.

## Build

```bash
cmake --build build