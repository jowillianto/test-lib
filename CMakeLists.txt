cmake_minimum_required(VERSION 3.28)
project(test-lib)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED true)

add_library(test-lib)
target_sources(test-lib
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/test-lib.hpp
    ${CMAKE_CURRENT_LIST_DIR}/src/random.hpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src/test-lib.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/random.cpp
)
target_include_directories(test-lib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)