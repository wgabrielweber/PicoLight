# Add library cpp files
add_library(SerialCommunication INTERFACE)
target_sources(SerialCommunication INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/SerialCommunication.cpp
)

# Add include directory for Logger.hpp
target_include_directories(SerialCommunication INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

# Add the standard library to the build
# target_link_libraries(Logger INTERFACE pico_stdlib)