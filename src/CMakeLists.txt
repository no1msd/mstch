find_package(Boost 1.54 REQUIRED)

set(mstch_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/include CACHE STRING "mstch include directory")

include_directories(
    ${mstch_INCLUDE_DIR}
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

set_property(TARGET mstch PROPERTY VERSION ${mstch_VERSION})

install(
    TARGETS mstch EXPORT mstchTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

install(
    FILES "${PROJECT_SOURCE_DIR}/include/mstch/mstch.hpp"
    DESTINATION include/mstch
    COMPONENT Devel)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/mstch/mstch-config-version.cmake"
    VERSION ${mstch_VERSION}
    COMPATIBILITY AnyNewerVersion)

export(
    EXPORT mstchTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/mstch/mstch-targets.cmake"
    NAMESPACE mstch::)

configure_file(
    "${PROJECT_SOURCE_DIR}/cmake/mstch-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/mstch/mstch-config.cmake")

install(
    EXPORT mstchTargets
    FILE mstch-targets.cmake
    NAMESPACE mstch::
    DESTINATION lib/cmake/mstch)

install(FILES
    "${PROJECT_SOURCE_DIR}/cmake/mstch-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/mstch/mstch-config-version.cmake"
    DESTINATION lib/cmake/mstch
    COMPONENT Devel)
