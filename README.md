# Test Lib
A Simple and Light C++23 modules based C++ testing library. 

## Example Usage
```cpp
import moderna.test_lib;
auto tester = moderna::test_lib::make_tester("Many entry test")
  .add_test("Some Name over here", [](){})
  .add_test("Another Name", [](){});

tester.print_or_exit();
```

## API Documentation
### Creating a Test
```cpp
import moderna.test_lib;
auto tester = moderna::test_lib::make_tester{ 
  "Many entry test", // Name of the test Suite,
  true, // Should runs be done in parallel, 
  false // Should run progress be printed;
}

auto tester_with_progress_hook = moderna::test_lib::make_tester(
  "Many entry test", // Entry test
  [](size_t progress){}, // Get the progress in a callback functino
  true, // Should runs be done in parallel
  false // Should run progress be printed
)
```

### Getting the Run Results
```cpp
import moderna.test_lib;
auto tester = moderna::test_lib::make_tester("Many entry test")
  .add_test("Some Name over here", [](){})
  .add_test("Another Name", [](){});

/*
  Runs all the tests. 
*/
moderna::test_lib::result_list<tester.test_count()> results = tester.run_all();
size_t ok_count = results.ok_count();
size_t err_count = results.err_count();
/*
  Prints all the test result and exit with the correct exit code if not all the tests exits 
  successfully
*/
tester.print_and_exit();
```

### Performing Assertions
```cpp
#include <vector>
import moderna.test_lib;
moderna::test_lib::assert_equal(1, 1);
moderna::test_lib::assert_lt(0, 1); // Asserts less than

// This can be done on vectors too
moderna::test_lib::assert_equal(
  std::vector<uint32_t>({1, 2, 3}), 
  std::vector<uint32_t>({1, 2, 3})
);
```
