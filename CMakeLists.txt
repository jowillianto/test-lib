cmake_minimum_required(VERSION 3.28)
project(test-lib)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED true)
set (CMAKE_CXX_SCAN_FOR_MODULES true)
add_compile_options("-g")

add_library(test_lib)
file (
  GLOB test_lib_ccm
  "${CMAKE_CURRENT_LIST_DIR}/src/*.ccm"
)
target_sources(test_lib
  PUBLIC
    FILE_SET CXX_MODULES FILES ${test_lib_ccm}
)
add_executable(
  test_lib_example_linked_list
  EXCLUDE_FROM_ALL 
  ${CMAKE_CURRENT_LIST_DIR}/test/linked_list.cpp
)
target_link_libraries(test_lib_example_linked_list test_lib)