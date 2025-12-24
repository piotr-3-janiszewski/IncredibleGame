cmake_minimum_required(VERSION 3.22)
project(IncredibleGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include tests)

add_subdirectory(source)

list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
include(CTest)
add_subdirectory(tests)
