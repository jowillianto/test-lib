# Test Lib
A Simple and Light C++23 modules based C++ testing library. 

## Example Usage
```cpp
import moderna.test_lib;

namespace test_lib = moderna::test_lib;

int main() {
  moderna::test_lib::add_test([](){}, "Some Name over here")
  .add_test([](){}, "Another Name").done();
  return test_lib::run_all_and_exit();
}
```

## API Documentation
### Creating a Test
```cpp
import moderna.test_lib;

namespace test_lib = moderna::test_lib;

struct a_new_test {
  void operator()() {
    test_lib::assert_true(true, "HAHA");
  }
};

int main() {
  test_lib::add_test(a_new_test{}); // Adds a test with name HAHA. 
  return test_lib::run_all_and_exit();
}
```

### Getting the Run Results
```cpp
import moderna.test_lib;

namespace test_lib = moderna::test_lib;

struct a_new_test {
  void operator()() {
    test_lib::assert_true(true, "HAHA");
  }
};

int main() {
  test_lib::add_test(a_new_test{}); // Adds a test with name HAHA. 
  std::vector<test_result> res = test_lib::run_tests();
}
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
