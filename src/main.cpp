import moderna.test_lib;
#include <concepts>

namespace test_lib = moderna::test_lib;

int main(int argc, const char **argv) {
  test_lib::test_setup<test_lib::setup_mode::SET_UP>::set_up(argc, argv);
  int err_count = test_lib::run_all_and_exit();
  test_lib::test_setup<test_lib::setup_mode::TEAR_DOWN>::tear_down();
  return err_count;
}