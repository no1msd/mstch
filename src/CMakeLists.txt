find_package(Boost 1.54 REQUIRED)

include_directories(
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}
	${Boost_INCLUDE_DIR})

set(SRC
	mstch.cpp
	utils.cpp
	token.cpp
	render_context.cpp
	state/in_section.cpp
	state/in_inverted_section.cpp
	state/outside_section.cpp
	visitor/is_node_empty.cpp
	visitor/render_node.cpp
	visitor/render_section.cpp)

add_library(mstch STATIC ${SRC})
