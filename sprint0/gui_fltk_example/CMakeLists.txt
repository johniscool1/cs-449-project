cmake_minimum_required(VERSION 3.10)
project(MyProgram)

# Define the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the FLTK source directory
set(FLTK_DIR "${CMAKE_SOURCE_DIR}/fltk-1.3.9")

# Add FLTK
add_subdirectory(${FLTK_DIR} ${CMAKE_BINARY_DIR}/fltk)

# Include directories
include_directories(${FLTK_DIR}/fltk/include)

# Add the executable
add_executable(gui_exmaple src/example_fltk_main.cpp)

# Link the FLTK library
target_link_libraries(gui_exmaple PRIVATE fltk)
