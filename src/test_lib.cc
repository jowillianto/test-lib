module;
#include <concepts>
export module moderna.test_lib;
export import :randomizer;
export import :exception;
export import :assert;
export import :test_suite;
export import :test_runner;
export import :test_entry;

namespace moderna::test_lib {
  export enum struct setup_mode { SET_UP, TEAR_DOWN };

  export template <setup_mode mode> struct test_setup {
    static void set_up(int argc, const char **argv) {}
    static void tear_down() {}
  };
}