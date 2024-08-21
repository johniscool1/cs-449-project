cmake_minimum_required(VERSION 3.10)
project(MyTests)


# Add the source file
add_executable(my_tests src/tests.cpp src/functions.cpp src/catch_amalgamated.cpp)