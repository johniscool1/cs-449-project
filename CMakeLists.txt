cmake_minimum_required(VERSION 3.28)
include(FetchContent)
project(complete_example_gui)


FetchContent_Declare(
  fltk
  URL      https://www.fltk.org/pub/fltk/1.3.9/fltk-1.3.9-source.tar.gz
)
set(FLTK_BUILD_EXAMPLES OFF CACHE BOOL "Disable building FLTK examples" FORCE)
set(FLTK_BUILD_TEST OFF CACHE BOOL "Disable building FLTK tests" FORCE)

FetchContent_MakeAvailable(fltk)


#add_subdirectory(fltk-1.3.9)
add_subdirectory(src)
