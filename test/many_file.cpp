import test_lib;
#include <format>

int main() {
  auto tester = test_lib::Tester<>{"Many entry test"}
                  .add_test(test_lib::random_string(10), []() {})
                  .add_test(test_lib::random_string(10), []() {})
                  .add_test(test_lib::random_string(10), []() {})
                  .add_test(test_lib::random_string(10), []() {})
                  .add_test(test_lib::random_string(10), []() {})
                  .add_test(test_lib::random_string(10), []() {})
                  .add_test(test_lib::random_string(10), []() {})
                  .add_test(test_lib::random_string(10), []() {})
                  .add_test(test_lib::random_string(10), []() {})
                  .add_test(test_lib::random_string(10), []() {})
                  .add_test(test_lib::random_string(10), []() {})
                  .add_test(test_lib::random_string(10), []() {})
                  .add_test(test_lib::random_string(10), []() {});
  tester.run_all();
  tester.print_or_exit();
}