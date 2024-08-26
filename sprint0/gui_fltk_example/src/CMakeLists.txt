cmake_minimum_required(VERSION 3.10)
project(MyProgram)

# Define the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the FLTK source directory
# Set the FLTK include and library directories (where FLTK is built)
set(FLTK_INCLUDE_DIR "${CMAKE_BINARY_DIR}/fltk-install/include")
set(FLTK_LIBRARY_DIR "${CMAKE_BINARY_DIR}/fltk-install/lib")

# Include FLTK headers
include_directories(${FLTK_INCLUDE_DIR})


# Add FLTK
#add_subdirectory(${FLTK_DIR} ${CMAKE_BINARY_DIR}/fltk)

# Include directories
#include_directories(../fltk-1.3.9)

# Add the executable
add_executable(gui_exmaple example_fltk_main.cpp)

# Link the FLTK library
target_link_libraries(gui_exmaple PRIVATE fltk)
