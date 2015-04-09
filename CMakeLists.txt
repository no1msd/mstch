cmake_minimum_required(VERSION 3.0.2 FATAL_ERROR)
project(mstch)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost 1.54 REQUIRED)
include_directories(src include vendor/include ${Boost_INCLUDE_DIR})

set(SRC
	src/mstch.cpp
	test/main.cpp)

add_executable(mstch ${SRC} include/types.h src/utils.h src/utils.cpp src/token.cpp src/token.h src/render_context.cpp src/render_context.h src/state/render_state.h src/state/in_section.cpp src/state/in_section.h src/state/in_inverted_section.cpp src/state/in_inverted_section.h src/state/outside_section.cpp src/state/outside_section.h src/visitor/is_node_empty.cpp src/visitor/is_node_empty.h src/visitor/render_node.cpp src/visitor/render_node.h src/visitor/render_section.cpp src/visitor/render_section.h src/visitor/to_json.cpp src/visitor/to_json.h)
