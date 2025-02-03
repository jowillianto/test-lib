module;
#include <algorithm>
#include <atomic>
#include <expected>
#include <optional>
#include <print>
#include <ranges>
#include <thread>
export module moderna.test_lib:test_runner;
import :test_suite;
import :test_config;

namespace moderna::test_lib {
  struct multithreaded_runner {
    multithreaded_runner(size_t pool_size) : __pool_size{pool_size} {}

    std::vector<test_result> run_test_suite(const test_suite &suite) const {
      std::atomic<size_t> cur_id;
      std::vector<std::thread> thread_pool;
      std::vector<test_result> results{suite.size()};
      thread_pool.reserve(__pool_size);
      for (size_t i = 0; i < __pool_size; i += 1) {
        thread_pool.emplace_back(std::thread{[&]() {
          size_t test_id = cur_id.fetch_add(1, std::memory_order_relaxed);
          while (test_id < suite.size()) {
            auto test_entry = suite.get(test_id).value();
            auto res = test_entry.get().run_test();
            results[test_id] = res;
            test_id = cur_id.fetch_add(1, std::memory_order_relaxed);
          }
        }});
      }
      for (size_t i = 0; i < __pool_size; i += 1) {
        thread_pool[i].join();
      }
      return results;
    }

  private:
    size_t __pool_size;
  };

  struct sequential_runner {
    std::vector<test_result> run_test_suite(const test_suite &suite) const {
      std::vector<test_result> results;
      results.reserve(suite.size());
      for (const auto &test : suite) {
        results.push_back(test->run_test());
      }
      return results;
    }
  };

  export std::vector<test_result> run_tests(
    size_t thread_count = 1, const test_suite &suite = get_global_test()
  ) {
    if (thread_count == 1) {
      auto runner = sequential_runner{};
      return runner.run_test_suite(suite);
    } else {
      auto runner = multithreaded_runner{thread_count};
      return runner.run_test_suite(suite);
    }
  }

  export std::expected<std::pair<size_t, size_t>, fail_assertion> print_test_result(
    const std::vector<test_result> &vec, const test_suite &suite
  ) {
    if (vec.size() != suite.size()) {
      return std::unexpected{fail_assertion{"Test suite and test result vector size mismatch"}};
    }
    size_t i = 1;
    size_t ok_count =
      std::ranges::count_if(vec, [](const test_result &res) { return res.is_ok(); });
    size_t err_count =
      std::ranges::count_if(vec, [](const test_result &res) { return res.is_error(); });
    std::println("Run {} tests", suite.size());
    std::println("OK: {}, Err: {}", ok_count, err_count);
    for (const auto &[res, test] : std::ranges::zip_view{vec, suite}) {
      if (res.is_ok()) {
        std::println("{}. Test {} OK\n", i, test->name());
      } else {
        std::println(
          "{}. Test {} ERR.\n{}({})\n",
          i,
          test->name(),
          res.get_error().value().name,
          res.get_error().value().message
        );
      }
      i += 1;
    }
    return std::pair{ok_count, err_count};
  }
  export int run_all_and_exit(
    size_t thread_count = 10, const test_suite &suite = get_global_test()
  ) {
    auto results = run_tests(thread_count, suite);
    auto [ok_count, err_count] = print_test_result(results, suite).value();
    return err_count;
  }
}