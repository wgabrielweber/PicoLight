add_library(Control INTERFACE)
target_sources(Control INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/Control.cpp
)

# Add include directory
target_include_directories(Control INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Add the include directory for additional headers
include_directories(include)

# Add the standard library to the build
target_link_libraries(Control INTERFACE pico_stdlib hardware_pio pico_stdlib hardware_rtc pico_util)