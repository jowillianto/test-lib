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
  test_lib::ResultList<tester.test_count()> results = tester.run_all();
  test_lib::assert_equal (results.ok_count(), tester.test_count());
}