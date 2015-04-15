find_package(Boost 1.54 REQUIRED)

include_directories(
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}
	${Boost_INCLUDE_DIR})

set(SRC
	state/in_inverted_section.cpp
	state/in_section.cpp
	state/outside_section.cpp
	visitor/is_node_empty.cpp
	visitor/render_node.cpp
	visitor/render_section.cpp
	mstch.cpp
	render_context.cpp
	template_type.cpp
	token.cpp
	utils.cpp)

add_library(mstch STATIC ${SRC})
