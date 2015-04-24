find_package(Boost 1.54 REQUIRED)

include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${Boost_INCLUDE_DIR})

set(SRC
  state/in_section.cpp
  state/outside_section.cpp
  state/render_state.hpp
  visitor/get_token.hpp
  visitor/has_token.hpp
  visitor/is_node_empty.hpp
  visitor/render_node.hpp
  visitor/render_section.hpp
  mstch.cpp
  render_context.cpp
  template_type.cpp
  token.cpp
  utils.cpp)

add_library(mstch STATIC ${SRC})

install(TARGETS mstch DESTINATION lib)
install(FILES ${CMAKE_SOURCE_DIR}/include/mstch/mstch.hpp DESTINATION include/mstch)