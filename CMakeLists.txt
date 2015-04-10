cmake_minimum_required(VERSION 3.0.2 FATAL_ERROR)
project(mstch)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

find_package(Boost 1.54 COMPONENTS program_options REQUIRED)
include_directories(${CMAKE_BINARY_DIR} src include vendor/include ${Boost_INCLUDE_DIR})

set(SRC
	src/mstch.cpp
	src/utils.cpp
	src/token.cpp
	src/render_context.cpp
	src/state/in_section.cpp
	src/state/in_inverted_section.cpp
	src/state/outside_section.cpp
	src/visitor/is_node_empty.cpp
	src/visitor/render_node.cpp
	src/visitor/render_section.cpp
	src/visitor/to_json.cpp)

add_library(mstch STATIC ${SRC})

add_executable(mstch_test test/main.cpp)
target_link_libraries(mstch_test mstch)

add_executable(filetoheader test/filetoheader.cpp)
target_link_libraries(filetoheader ${Boost_PROGRAM_OPTIONS_LIBRARY})

add_custom_command(
	OUTPUT ${CMAKE_BINARY_DIR}/test_data.h
	COMMAND ${CMAKE_BINARY_DIR}/filetoheader --output ${CMAKE_BINARY_DIR}/test_data.h --namespace mstchtest
		-Dampersand_escape.h -Sampersand_escape.mustache -Sampersand_escape.txt
		-Dapostrophe.h -Sapostrophe.mustache -Sapostrophe.txt
		-Darray_of_strings.h -Sarray_of_strings.mustache -Sarray_of_strings.txt
		-Dbackslashes.h -Sbackslashes.mustache -Sbackslashes.txt
		-Dbug_11_eating_whitespace.h -Sbug_11_eating_whitespace.mustache -Sbug_11_eating_whitespace.txt
		-Dbug_length_property.h -Sbug_length_property.mustache -Sbug_length_property.txt
		-Dcontext_lookup.h -Scontext_lookup.mustache -Scontext_lookup.txt
		-Ddisappearing_whitespace.h -Sdisappearing_whitespace.mustache -Sdisappearing_whitespace.txt
		-Ddouble_render.h -Sdouble_render.mustache -Sdouble_render.txt
		-Dempty_list.h -Sempty_list.mustache -Sempty_list.txt
		-Dempty_sections.h -Sempty_sections.mustache -Sempty_sections.txt
		-Dempty_string.h -Sempty_string.mustache -Sempty_string.txt
		-Dempty_template.h -Sempty_template.mustache -Sempty_template.txt
		-Derror_not_found.h -Serror_not_found.mustache -Serror_not_found.txt
		-Dfalsy.h -Sfalsy.mustache -Sfalsy.txt
	DEPENDS ${CMAKE_BINARY_DIR}/filetoheader
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test/data/)
set_source_files_properties(${CMAKE_BINARY_DIR}/test_data.h PROPERTIES GENERATED TRUE)
add_custom_target(test_data_h DEPENDS ${CMAKE_BINARY_DIR}/test_data.h)
add_dependencies(mstch test_data_h)
