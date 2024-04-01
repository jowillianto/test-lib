import test_lib;

int main() {
  auto tester = test_lib::Tester<>{ "Many entry test" }
    .add_test(test_lib::random_string(10), [](){})
    .add_test(test_lib::random_string(10), [](){})
    .add_test(test_lib::random_string(10), [](){})
    .add_test(test_lib::random_string(10), [](){})
    .add_test(test_lib::random_string(10), [](){})
    .add_test(test_lib::random_string(10), [](){})
    .add_test(test_lib::random_string(10), [](){})
    .add_test(test_lib::random_string(10), [](){})
    .add_test(test_lib::random_string(10), [](){})
    .add_test(test_lib::random_string(10), [](){})
    .add_test(test_lib::random_string(10), [](){})
    .add_test(test_lib::random_string(10), [](){})
    .add_test(test_lib::random_string(10), [](){});
  test_lib::print_result(tester, tester.run_all());
}