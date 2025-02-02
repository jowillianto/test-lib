import moderna.test_lib;
#include <stdexcept>

namespace test_lib = moderna::test_lib;

struct create_with_struct_name {
  void operator()() const {
    test_lib::assert_equal(
      test_lib::get_global_test().get(0).value().get().name(), "create_with_struct_name"
    );
  }
};

struct create_with_custom_name {
  void operator()() const {
    test_lib::assert_equal(test_lib::get_global_test().get(0).value().get().name(), "custom_name");
  }
};

struct run_throw_runtime_error {
  void operator()() const {
    auto conf = test_lib::test_config{[]() { throw std::runtime_error("LOL"); }};
    auto res = conf.run_test();
    test_lib::assert_equal(res.is_error(), true);
    test_lib::assert_equal(res.get_error().value().name, "runtime_error");
    test_lib::assert_equal(res.get_error().value().message, "LOL");
  }
};

int main() {
  test_lib::add_test(create_with_struct_name{})
    .add_test(create_with_custom_name{}, "custom_name")
    .add_test(run_throw_runtime_error{})
    .done();
  return test_lib::run_all_and_exit();
}