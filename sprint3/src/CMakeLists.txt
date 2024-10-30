cmake_minimum_required(VERSION 3.10)
project(SOS)

# Define the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the FLTK source directory
# Set the FLTK include and library directories (where FLTK is built)
#set(FLTK_INCLUDE_DIR "${CMAKE_BINARY_DIR}/fltk-install/include")
#set(FLTK_LIBRARY_DIR "${CMAKE_BINARY_DIR}/fltk-install/lib")

# Include FLTK headers
#include_directories(${FLTK_INCLUDE_DIR})


# Add FLTK
#add_subdirectory(${FLTK_DIR} ${CMAKE_BINARY_DIR}/fltk)

# Include directories
include_directories(../_deps/fltk-src)
include_directories(../_deps/fltk-build)
include_directories(/usr/local/include)
include_directories(/usr/local/lib)


#debug
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
# Add the executable
add_executable(sprint2sos main.cpp screen_def.cpp game_logic.cpp)

# Link the FLTK library
target_link_libraries(sprint2sos PRIVATE fltk)

#Build unit tests
# Add the executable
add_executable(unit_tests unit_tests.cpp screen_def.cpp game_logic.cpp test_lib/catch_amalgamated.cpp)

# Link the FLTK library
target_link_libraries(unit_tests PRIVATE fltk m stdc++)
