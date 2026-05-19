cmake_minimum_required(VERSION 3.15)

project(spacecraft_flight_software_sim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(spacecraft_sim
    src/main.cpp
    src/spacecraft.cpp
    src/power.cpp
    src/thermal.cpp
    src/comms.cpp
    src/fault_manager.cpp
    src/scheduler.cpp
    src/telemetry_logger.cpp
)

add_executable(test_power
    tests/test_power.cpp
    src/power.cpp
)

add_executable(test_scheduler
    tests/test_scheduler.cpp
    src/scheduler.cpp
)

add_executable(test_fault_manager
    tests/test_fault_manager.cpp
    src/fault_manager.cpp
)
add_executable(test_comms
    tests/test_comms.cpp
    src/comms.cpp
)

add_executable(test_thermal
    tests/test_thermal.cpp
    src/thermal.cpp
)

add_executable(test_mode
    tests/test_mode.cpp
)