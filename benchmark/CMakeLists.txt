include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/vendor/benchmark/include)

add_executable(mstch_benchmark benchmark_main.cpp)
target_link_libraries(mstch_benchmark mstch benchmark)
