import moderna.test_lib;
#include <format>
using namespace moderna;

int main() {
  auto tester = test_lib::make_tester("Many entry test")
                  .add_test("entry 1", []() {})
                  .add_test("entry 2", []() {})
                  .add_test("entry 3", []() {})
                  .add_test("entry 4", []() {})
                  .add_test("entry 5", []() {})
                  .add_test("entry 6", []() {})
                  .add_test("entry 7", []() {})
                  .add_test("entry 8", []() {})
                  .add_test("entry 9", []() {})
                  .add_test("entry 10", []() {})
                  .add_test("entry 11", []() {})
                  .add_test("entry 12", []() {})
                  .add_test("entry 13", []() {});
  tester.run_all();
  tester.print_or_exit();
}