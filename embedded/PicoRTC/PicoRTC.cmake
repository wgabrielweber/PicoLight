# Add library cpp files
add_library(PicoRTC INTERFACE)
target_sources(PicoRTC INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/BH1750FVI.cpp
)

# Add include directory
target_include_directories(PicoRTC INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Add the include directory for additional headers
include_directories(include)

# Add the standard library to the build
target_link_libraries(PicoRTC INTERFACE pico_stdlib hardware_rtc pico_util)