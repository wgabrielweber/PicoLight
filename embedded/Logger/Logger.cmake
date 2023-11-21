# Add library cpp files
add_library(Logger INTERFACE)
target_sources(Logger INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/Logger.cpp
)

# Add include directory for Logger.hpp
target_include_directories(Logger INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

# Add the standard library to the build
# target_link_libraries(Logger INTERFACE pico_stdlib)



