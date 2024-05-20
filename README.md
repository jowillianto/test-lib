# Test Lib
A Simple and Light C++23 modules based C++ testing library. 

## Example Usage
```cpp
import test_lib;
auto tester = test_lib::Tester<>{ "Many entry test" }
  .add_test("Some Name over here", [](){})
  .add_test("Another Name", [](){});

// Run and print
test_lib::run_all_and_print(tester);
```

## API Documentation
### Creating a Test
```cpp
import test_lib;
auto tester = test_lib::Tester<>{ 
  "Many entry test", // Name of the test Suite,
  true, // Should runs be done in parallel, 
  false // Should run progress be printed;
}

auto tester_with_progress_hook = test_lib::Tester<>{
  "Many entry test", // Entry test
  [](size_t progress){}, // Get the progress in a callback functino
  true, // Should runs be done in parallel
  false // Should run progress be printed
}
```

### Getting the Run Results
```cpp
import test_lib;
auto tester = test_lib::Tester<>{ "Many entry test" }
  .add_test("Some Name over here", [](){})
  .add_test("Another Name", [](){});

/*
  Runs all the tests. 
*/
const test_lib::ResultList<tester.test_count()>& results = tester.run_all();
size_t ok_count = results.ok_count();
size_t err_count = results.err_count();
std::array<TestResult, tester.test_count()> result_array& = tester.array;
/*
  Prints all the test result and exit with the correct exit code if not all the tests exits 
  successfully
*/
tester.print_and_exit();
```

### Performing Assertions
```cpp
#include <vector>
import test_lib;
test_lib::assert_equal(1, 1);
test_lib::assert_lt(0, 1); // Asserts less than

// This can be done on vectors too
test_lib::assert_equal(
  std::vector<uint32_t>({1, 2, 3}), 
  std::vector<uint32_t>({1, 2, 3})
);
```
