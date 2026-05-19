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
)