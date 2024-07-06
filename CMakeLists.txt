cmake_minimum_required(VERSION 3.28)
project(moderna_test_lib)
set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED true)
set (CMAKE_CXX_SCAN_FOR_MODULES true)
set (CMAKE_CXX_COMPILE_FEATURES "-Wall -Werror")

include (CTest)

if (NOT TARGET ${PROJECT_NAME})
  add_library(${PROJECT_NAME})
  file (
    GLOB ${PROJECT_NAME}_src
    "${CMAKE_CURRENT_LIST_DIR}/src/*.ccm"
  )
  target_sources(${PROJECT_NAME}
    PUBLIC
      FILE_SET CXX_MODULES FILES ${${PROJECT_NAME}_src}
  )
endif()

# Function to add a test into the suite. 
function(moderna_add_test target_name target_files)
  set(options)
  set(oneValueArgs)
  set(multiValueArgs 
    LIBRARIES
    DIRECTORIES
    SANITIZERS
    COMPILE_DEFINITIONS
    COMPILE_OPTIONS
    COMPILE_FEATURES
    LINK_OPTIONS
  )
  cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  # This adds the non sanitized test
  include(CTest)
  add_executable(${target_name} ${target_files})

  function (add_sanitizer target_name sanitizer abbr)
    add_executable(${target_name}_${abbr} ${target_files})
    
    if(ARG_LIBRARIES)
      target_link_libraries(${target_name}_${abbr} PRIVATE ${ARG_LIBRARIES})
    endif()
    if(ARG_COMPILE_DEFINITIONS)
      target_compile_definitions(${target_name}_${abbr} PRIVATE ${ARG_COMPILE_DEFINITIONS})
    endif()
    if (ARG_DIRECTORIES)
      target_include_directories(${target_name}_${abbr} PRIVATE ${ARG_DIRECTORIES})
    endif()
    if (ARG_LINK_OPTIONS)
      target_link_options(${target_name}_${abbr} PRIVATE "-fsanitize=${sanitizer}" ${ARG_LINK_OPTIONS})
    else()
      target_link_options(${target_name}_${abbr} PRIVATE "-fsanitize=${sanitizer}")
    endif()
    if (ARG_COMPILE_OPTIONS)
      target_compile_options(${target_name}_${abbr} PRIVATE "-fsanitize=${sanitizer}" ${ARG_COMPILE_OPTIONS})
    else()
      target_compile_options(${target_name}_${abbr} PRIVATE "-fsanitize=${sanitizer}")
    endif()
    if (ARG_COMPILE_FEATURES)
      target_compile_features(${target_name}_${abbr} PRIVATE ${ARG_COMPILE_FEATURES})
    endif()
    add_test(NAME ${target_name}_${abbr} COMMAND ${target_name}_${abbr})
  endfunction()

  # Normal Addition
  if (ARG_LIBRARIES)
    target_link_libraries(${target_name} PRIVATE ${ARG_LIBRARIES})
  endif()
  if (ARG_COMPILE_DEFINITIONS)
    target_compile_definitions(${target_name} PRIVATE ${ARG_COMPILE_DEFINITIONS})
  endif()
  if (ARG_DIRECTORIES)
    target_include_directories(${target_name} PRIVATE ${ARG_DIRECTORIES})
  endif()
  if (ARG_LINK_OPTIONS)
    target_link_options(${target_name} PRIVATE ${ARG_LINK_OPTIONS})
  endif()
  if (ARG_COMPILE_OPTIONS)
    target_compile_options(${target_name} PRIVATE ${ARG_COMPILE_OPTIONS})
  endif()
  if (ARG_COMPILE_FEATURES)
    target_compile_features(${target_name} PRIVATE ${ARG_COMPILE_FEATURES})
  endif()
  add_test(NAME ${target_name} COMMAND ${target_name})

  if ("all" IN_LIST ARG_SANITIZERS)
    add_sanitizer(${target_name} "address" "asan")
    add_sanitizer(${target_name} "thread" "tsan")
    add_sanitizer(${target_name} "undefined" "ubsan")
    if (NOT APPLE)
      add_sanitizer(${target_name} "undefined" "ubsan")
    endif()
  else()
    if ("address" IN_LIST ARG_SANITIZERS)
      add_sanitizer(${target_name} "address" "asan")
    endif()
    if ("thread" IN_LIST ARG_SANITIZERS)
      add_sanitizer(${target_name} "thread" "tsan")
    endif()
    if ("undefined" IN_LIST ARG_SANITIZERS)
      add_sanitizer(${target_name} "undefined" "ubsan")
    endif()
    if ("memory" IN_LIST ARG_SANITIZERS AND NOT APPLE)
      add_sanitizer(${target_name} "memory" "msan")
    endif()
  endif()
endfunction()

if (PROJECT_IS_TOP_LEVEL)
  moderna_add_test(
    ${PROJECT_NAME}_linked_list 
    ${CMAKE_CURRENT_LIST_DIR}/test/linked_list.cpp
    LIBRARIES ${PROJECT_NAME}
    SANITIZERS all
  )
  moderna_add_test(
    ${PROJECT_NAME}_multithread_cache  
    ${CMAKE_CURRENT_LIST_DIR}/test/multithread_cache.cpp
    LIBRARIES ${PROJECT_NAME}
    SANITIZERS all
  )
  moderna_add_test(
    ${PROJECT_NAME}_many_file 
    ${CMAKE_CURRENT_LIST_DIR}/test/many_file.cpp
    LIBRARIES ${PROJECT_NAME}
    SANITIZERS all
  )
elseif (PROJECT_IS_TOP_LEVEL)
  message ("To run tests clone https://github.com/jowillianto/moderna")
endif()
