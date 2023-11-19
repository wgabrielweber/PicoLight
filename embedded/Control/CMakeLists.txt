 # Author: Gabriel Weber Berwian < wgabrielweber@hotmail.com >
 # Institution: UFSC
 # Date: 18/11/2023
 # File: CMakeLists.txt
 
# Set minimum required version of CMake

# Generated Cmake Pico project file
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(Control C CXX ASM)
set(PICO_CXX_ENABLE_EXCEPTIONS 1)
set(PICO_CXX_ENABLE_RTTI 1)

# Initialise the Pico SDK
pico_sdk_init()

include("../Actuator/PicoLed/PicoLed.cmake")
include("../ClockCalendar/ClockCalendar.cmake")
include("../Sensor/Sensor.cmake")

# Add executable. Default name is the project name, version 0.1
add_executable(Control Control.cpp )

pico_set_program_name(Control "Control")
pico_set_program_version(Control "0.1")

pico_enable_stdio_uart(Control 0)
pico_enable_stdio_usb(Control 1)

# Add the standard library to the build
target_link_libraries(Control 
        pico_stdlib
        hardware_i2c
        PicoLed
        ClockCalendar
        Sensor
)

# Add include directories for ClockCalendar and other components
target_include_directories(Control PRIVATE
    "../ClockCalendar/include"  # Add the path to ClockCalendar.hpp
    "../Actuator/PicoLed"       # Add the path to PicoLed.hpp
    "../Sensor/include"         # Add the path to BH1750FVI.hpp
)

pico_add_extra_outputs(Control)