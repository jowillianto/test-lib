
module;

#include <format>
#include <ranges>
#include <source_location>

export module moderna.test_lib:assert;
import :exception;

namespace moderna::test_lib {
  template <typename T, typename V>
  concept equal_comp = requires(const T &x, const V &v) {
    { x == v } -> std::convertible_to<bool>;
  };
  template <typename T, typename V>
  concept lt_comp = requires(const T &x, const V &v) {
    { x < v } -> std::convertible_to<bool>;
  };

  /*
    Checks the equality of two values x and y. Throw a fail_assertion exception when the assertion
    fails. When used in the scope of a tester, exception will be caught and will invalidate the
    test.
  */
  export template <typename T, equal_comp<T> V>
  void assert_equal(
    const T &x, const V &y, std::source_location location = std::source_location::current()
  ) {
    if (x != y) {
      if constexpr (std::formattable<T, char> && std::formattable<V, char>) {
        throw fail_assertion(std::format(
          "At {} Line {} , {} is not equal to {}", location.file_name(), location.line(), x, y
        ));
      } else {
        throw fail_assertion(
          std::format("Assertion error at line {} file {}", location.line(), location.file_name())
        );
      }
    }
  }

  /*
    Checks if x is less than y. Throw a fail_assertion exception when the assertion
    fails. When used in the scope of a tester, exception will be caught and will invalidate the
    test.
  */
  export template <typename T, equal_comp<T> V>
  void assert_lt(
    const T &x, const V &y, std::source_location location = std::source_location::current()
  ) {
    if (x >= y) {
      if constexpr (std::formattable<T, char> && std::formattable<V, char>) {
        throw fail_assertion(std::format(
          "At {} Line {} , {} is not less than {}", location.file_name(), location.line(), x, y
        ));
      } else {
        throw fail_assertion(
          std::format("Assertion error at line {} file {}", location.line(), location.file_name())
        );
      }
    }
  }

  /*
    Cheks the equality of two containers supporting the ranges paradigm.
  */
  export template <std::ranges::forward_range T, std::ranges::forward_range V>
    requires(equal_comp<std::ranges::range_value_t<T>, std::ranges::range_value_t<V>> && !equal_comp<T, V>)
  void assert_equal(
    const T &x, const V &y, std::source_location location = std::source_location::current()
  ) {
    auto beg_x = std::ranges::begin(x);
    auto end_x = std::ranges::end(x);
    auto beg_y = std::ranges::begin(y);
    auto end_y = std::ranges::end(y);
    size_t idx = 0;
    while (beg_x != end_x && beg_y != end_y) {
      try {
        assert_equal(*beg_x, *beg_y);
      } catch (const fail_assertion &e) {
        throw fail_assertion(std::format("{} at index {}", e.msg(), idx));
      }
      beg_y += 1;
      beg_x += 1;
      idx += 1;
    }
  }

  export template <std::ranges::forward_range T, std::ranges::forward_range V>
    requires(equal_comp<std::ranges::range_value_t<T>, std::ranges::range_value_t<V>> && !equal_comp<T, V>)
  void assert_lt(
    const T &x, const V &y, std::source_location location = std::source_location::current()
  ) {
    auto beg_x = std::ranges::begin(x);
    auto end_x = std::ranges::end(x);
    auto beg_y = std::ranges::begin(y);
    auto end_y = std::ranges::end(y);
    size_t idx = 0;
    while (beg_x != end_x && beg_y != end_y) {
      try {
        assert_lt(*beg_x, *beg_y);
      } catch (const fail_assertion &e) {
        throw fail_assertion(std::format("{} at index {}", e.msg(), idx));
      }
      beg_y += 1;
      beg_x += 1;
      idx += 1;
    }
  }

  export void assert_true(
    bool expr,
    std::string_view err_msg,
    std::source_location location = std::source_location::current()
  ) {
    if (!expr) {
      throw fail_assertion(
        std::format("At {} Line {} , {}", location.file_name(), location.line(), err_msg)
      );
    }
  }
}