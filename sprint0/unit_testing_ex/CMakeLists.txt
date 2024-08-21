cmake_minimum_required(VERSION 3.10)
project(MyTests)


# Add the source file
add_executable(my_tests tests.cpp functions.cpp catch_amalgamated.cpp)

