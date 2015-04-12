cmake_minimum_required(VERSION 3.0.2 FATAL_ERROR)
project(mstch)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME mstch_tests COMMAND mstch_test)
