cmake_minimum_required(VERSION 3.22)
project(IncredibleGame)

set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED True)

include_directories(include)

add_subdirectory(source)

list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
include(CTest)
add_subdirectory(tests)
