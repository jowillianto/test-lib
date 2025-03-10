moderna_add_test(
  ${PROJECT_NAME}_asserts
  ${CMAKE_CURRENT_LIST_DIR}/asserts.cc
  SANITIZERS all
)

moderna_add_test(
  ${PROJECT_NAME}_tests
  ${CMAKE_CURRENT_LIST_DIR}/tests.cc
  SANITIZERS all
)