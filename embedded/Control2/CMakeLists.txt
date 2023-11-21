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
project(ctrlTest C CXX ASM)
set(PICO_CXX_ENABLE_EXCEPTIONS 1)
set(PICO_CXX_ENABLE_RTTI 1)

# Initialise the Pico SDK
pico_sdk_init()

# Add the include directory for additional headers
include_directories(include)

include("../Actuator/PicoLed/PicoLed.cmake")
include("../Sensor/Sensor.cmake")
include("Control.cmake")

# Add executable. Default name is the project name, version 0.1
add_executable(ctrlTest 
        Control.cpp
        ctrlTest.cpp
)

pico_set_program_name(ctrlTest "ctrlTest")
pico_set_program_version(ctrlTest "0.1")

pico_enable_stdio_uart(ctrlTest 0)
pico_enable_stdio_usb(ctrlTest 1)

# Add the standard library to the build
target_link_libraries(ctrlTest 
        pico_stdlib
        hardware_i2c
        PicoLed
        Sensor
)

# Add include directories for other components
target_include_directories(ctrlTest PRIVATE
    "../Actuator/PicoLed"       # path to PicoLed.hpp
    "../Sensor/include"         # path to BH1750FVI.hpp
    "include"                   # path to Control.hpp
)

pico_add_extra_outputs(ctrlTest)