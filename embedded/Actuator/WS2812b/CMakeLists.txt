 # Author: Gabriel Weber Berwian < wgabrielweber@hotmail.com >
 # Institution: UFSC
 # Date: 16/11/2023
 # File: CMakeLists.txt
 
# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(ws2812b C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# Add the include directory for additional headers
include_directories(
        ../PicoPWM/include
        include
)

# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME}
        ../PicoPWM/pwm_control.cpp
        WS2812b.cpp
        WS2812b_test.cpp
)

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${PROJECT_NAME}
        pico_stdlib
        hardware_irq
        hardware_pwm
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# add url via pico_set_program_url
# example_auto_set_url(${PROJECT_NAME})

