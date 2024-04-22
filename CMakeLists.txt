cmake_minimum_required(VERSION 3.28)
project(test-lib)
set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED true)
set (CMAKE_CXX_SCAN_FOR_MODULES true)
set (CMAKE_CXX_COMPILE_FEATURES "-Wall -Werror")

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
add_executable(
  test_lib_example_multithread_cache
  EXCLUDE_FROM_ALL 
  ${CMAKE_CURRENT_LIST_DIR}/test/multithread_cache.cpp
)
add_executable(
  test_lib_example_many_file
  EXCLUDE_FROM_ALL 
  ${CMAKE_CURRENT_LIST_DIR}/test/many_file.cpp
)
target_link_libraries(test_lib_example_linked_list test_lib)
target_link_libraries(test_lib_example_multithread_cache test_lib)
target_link_libraries(test_lib_example_many_file test_lib)
