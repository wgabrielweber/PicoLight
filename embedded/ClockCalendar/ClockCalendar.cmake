# Add library cpp files
add_library(ClockCalendar INTERFACE)
target_sources(ClockCalendar INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/Clock.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Calendar.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ClockCalendar.cpp
)

# Add include directory
target_include_directories(ClockCalendar INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Add the include directory for additional headers
include_directories(include)

# Add the standard library to the build
target_link_libraries(ClockCalendar INTERFACE pico_stdlib hardware_pio pico_stdlib hardware_rtc pico_util)