import moderna.test_lib;
#include <moderna/test_lib.hpp>
#include <print>
#include <stdexcept>

namespace test_lib = moderna::test_lib;

MODERNA_ADD_TEST(create_with_struct_name) {
  test_lib::assert_equal(
    test_lib::get_global_test().get(0).value().get().name(), "create_with_struct_name"
  );
}

MODERNA_ADD_TEST(custom_name) {
  test_lib::assert_equal(test_lib::get_global_test().get(1).value().get().name(), "custom_name");
}

MODERNA_ADD_TEST(run_throw_runtime_error) {
  auto conf = test_lib::test_entry{[]() { throw std::runtime_error("LOL"); }};
  auto res = conf.run_test();
  test_lib::assert_equal(res.is_error(), true);
  test_lib::assert_equal(res.get_error().value().name, "std::runtime_error");
  test_lib::assert_equal(res.get_error().value().message, "LOL");
}

MODERNA_SETUP(argc, argv) {
  test_lib::set_thread_count(1);
}

/*
  It is here for proof of concept.
*/
MODERNA_TEARDOWN() {
  test_lib::unset_thread_count();
}