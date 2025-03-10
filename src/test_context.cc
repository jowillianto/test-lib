module;
#include <array>
#include <chrono>
export module moderna.test_lib:test_context;
import :test_suite;

namespace moderna::test_lib {

  export enum struct test_time_unit { MICRO_SECONDS, MILLI_SECONDS, SECONDS };

  struct test_context {
    int thread_count = 1;
    test_suite tests = test_suite{};
    test_time_unit time_unit = test_time_unit::MICRO_SECONDS;

    std::string get_time(const std::chrono::system_clock::duration &dur) {
      if (time_unit == test_time_unit::MICRO_SECONDS) {
        return std::format(
          "{:.2f} μs",
          static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count()) /
            1000
        );
      } else if (time_unit == test_time_unit::MILLI_SECONDS) {
        return std::format(
          "{:.2f} ms",
          static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(dur).count()) /
            1000
        );
      } else {
        return std::format(
          "{:.2f} s",
          static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(dur).count()) /
            1000
        );
      }
    }
  };

  auto ctx = test_context{};

  export test_context &get_test_context() {
    return ctx;
  }
}