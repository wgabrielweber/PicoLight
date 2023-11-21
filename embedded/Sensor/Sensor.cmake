# Add library cpp files
add_library(Sensor INTERFACE)
target_sources(Sensor INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/BH1750FVI.cpp
)

# Add include directory
target_include_directories(Sensor INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Add the include directory for additional headers
include_directories(include)

# Add the standard library to the build
target_link_libraries(Sensor INTERFACE pico_stdlib hardware_i2c)