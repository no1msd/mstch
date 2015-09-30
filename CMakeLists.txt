cmake_minimum_required(VERSION 3.0.2)
project(mstch)
option (WITH_UNIT_TESTS "enable building unit test executable" OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)
set(CMAKE_BUILD_TYPE Release)

set(mstch_VERSION 0.2.3)

if(NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O3")
endif()

add_subdirectory(src)

if(WITH_UNIT_TESTS)
  enable_testing()
  include_directories(
      vendor/Catch/single_include
      vendor/json.hpp/include)
  add_subdirectory(test)
endif()
