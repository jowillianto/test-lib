cmake_minimum_required(VERSION 3.28)
project(moderna_test_lib)
set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED true)
set (CMAKE_CXX_SCAN_FOR_MODULES true)
set (CMAKE_CXX_COMPILE_FEATURES "-Wall -Werror")

include (CTest)

add_library(moderna_test_lib)
file (
  GLOB moderna_test_lib_src
  "${CMAKE_CURRENT_LIST_DIR}/src/*.ccm"
)
target_sources(moderna_test_lib
  PUBLIC
    FILE_SET CXX_MODULES FILES ${moderna_test_lib_src}
)

if (EXISTS ${CMAKE_CURRENT_LIST_DIR}/../../cmake/CMakeLists.txt AND PROJECT_IS_TOP_LEVEL)
  include (${CMAKE_CURRENT_LIST_DIR}/../../cmake/CMakeLists.txt)
  add_test_asan_tsan_usan_ubsan(
    moderna_test_lib_linked_list 
    ${CMAKE_CURRENT_LIST_DIR}/test/linked_list.cpp
    moderna_test_lib
  )
  add_test_asan_tsan_usan_ubsan(
    moderna_test_lib_multithread_cache  
    ${CMAKE_CURRENT_LIST_DIR}/test/multithread_cache.cpp
    moderna_test_lib
  )
  add_test_asan_tsan_usan_ubsan(
    moderna_test_lib_many_file 
    ${CMAKE_CURRENT_LIST_DIR}/test/many_file.cpp
    moderna_test_lib
  )
else()
  message ("To run tests clone https://github.com/jowillianto/moderna")
endif()
