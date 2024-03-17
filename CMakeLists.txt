cmake_minimum_required(VERSION 3.28)
project(test-lib)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED true)
set (CMAKE_CXX_SCAN_FOR_MODULES true)

add_library(test-lib)
target_sources(test-lib
  PUBLIC 
    FILE_SET CXX_MODULES FILES
      ${CMAKE_CURRENT_LIST_DIR}/src/test-lib.ccm
      ${CMAKE_CURRENT_LIST_DIR}/src/randomizer.ccm
      ${CMAKE_CURRENT_LIST_DIR}/src/data.ccm
      ${CMAKE_CURRENT_LIST_DIR}/src/exception.ccm
)

add_executable(main)
target_sources(main PRIVATE ${CMAKE_CURRENT_LIST_DIR}/test/main.cpp)
target_link_libraries(main test-lib)