find_package(Boost 1.54 REQUIRED)

include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/vendor/Catch/single_include
  ${CMAKE_SOURCE_DIR}/vendor/json.hpp/include
  ${Boost_INCLUDE_DIR})

file(GLOB data_files RELATIVE
  "${CMAKE_SOURCE_DIR}/test/data"
  "${CMAKE_SOURCE_DIR}/test/data/*.hpp")

foreach(data_file ${data_files})
  string(REGEX REPLACE "\\.hpp" "" test_name "${data_file}")
  list(APPEND tests "${test_name}")
endforeach(data_file)

file(GLOB string_files RELATIVE
  "${CMAKE_SOURCE_DIR}/test/data"
  "${CMAKE_SOURCE_DIR}/test/data/*.mustache"
  "${CMAKE_SOURCE_DIR}/test/data/*.txt"
  "${CMAKE_SOURCE_DIR}/test/data/*.partial")

foreach(string_file ${string_files})
  list(APPEND genargs "-i${string_file}")
endforeach(string_file)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/test_data.hpp
  COMMAND headerize --output ${CMAKE_CURRENT_BINARY_DIR}/test_data.hpp --namespace mstchtest ${genargs}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test/data/)
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/test_data.hpp PROPERTIES GENERATED TRUE)
add_custom_target(test_data_hpp DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/test_data.hpp)

file(GLOB specs_files RELATIVE
  "${CMAKE_SOURCE_DIR}/vendor/spec/specs"
  "${CMAKE_SOURCE_DIR}/vendor/spec/specs/*.json")

foreach(specs_file ${specs_files})
  list(APPEND specsargs "-i${specs_file}")
  string(REGEX REPLACE "\\.json" "" test_name "${specs_file}")
  string(REGEX REPLACE "~" "" test_name "${test_name}")
  list(APPEND tests "specs_${test_name}")
endforeach(specs_file)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/specs_data.hpp
  COMMAND headerize --output ${CMAKE_CURRENT_BINARY_DIR}/specs_data.hpp --namespace mstchtest ${specsargs}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/vendor/spec/specs/)
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/specs_data.hpp PROPERTIES GENERATED TRUE)
add_custom_target(specs_data_hpp DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/specs_data.hpp)

add_executable(mstch_test test_main.cpp)
target_link_libraries(mstch_test mstch)
add_dependencies(mstch_test test_data_hpp specs_data_hpp)

foreach(test ${tests})
  add_test(NAME ${test} COMMAND mstch_test ${test})
endforeach(test)
