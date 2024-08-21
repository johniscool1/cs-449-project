cmake_minimum_required(VERSION 3.10)
project(gui_example)

# Find FLTK package
find_package(FLTK REQUIRED)

# Include FLTK directories
include_directories(${FLTK_INCLUDE_DIR})

# Add the executable
add_executable(gui_example src/example_source/example_fltk_main.cpp)

# Link FLTK libraries
target_link_libraries(gui_example ${FLTK_LIBRARIES})