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
project(main C CXX ASM)
set(PICO_CXX_ENABLE_EXCEPTIONS 1)
set(PICO_CXX_ENABLE_RTTI 1)

# Initialise the Pico SDK
pico_sdk_init()

include("../Actuator/PicoLed/PicoLed.cmake")
include("../Control2/Control.cmake")
include("../Logger/Logger.cmake")
include("../Sensor/Sensor.cmake")

# Add executable. Default name is the project name, version 0.1
add_executable(main main.cpp )

pico_set_program_name(main "main")
pico_set_program_version(main "0.1")

pico_enable_stdio_uart(main 0)
pico_enable_stdio_usb(main 1)

# Add the standard library to the build
target_link_libraries(main 
        pico_stdlib
        pico_util
        hardware_i2c
        hardware_rtc
        PicoLed
        Sensor
        Control
        Logger
)

# Add include directories for other components
target_include_directories(main PRIVATE
    "../Actuator/PicoLed"       # path to PicoLed.hpp
    "../Sensor/include"         # path to BH1750FVI.hpp
    "../Control2/include"       # path to Control.hpp
    "../Logger/include"         # path to Logger.hpp
)

pico_add_extra_outputs(main)