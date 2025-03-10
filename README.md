# Test Lib
A Simple and Light C++23 modules based C++ testing library. 

## Example Usage
```cpp
import moderna.test_lib;

namespace test_lib = moderna::test_lib;
#include <moderna/test_lib.hpp>

MODERNA_ADD_TEST(some_name) {
  /*
    Do something over here
  */
}
```
The above will add the test into the test list. Compiling this file using cmake with `moderna_add_test` will result in the test being added and run automatically. 

# Documentation
## 1. Macros
- `MODERNA_ADD_TEST(test_name)`
This macro creates a function that will add a function declared after it into the test set. An example of adding a test is as follows : 
```
import moderna.test_lib;
#include <moderna/test_lib.hpp>

MODERNA_ADD_TEST() {}
```
- `MODERNA_SETUP(argc, argv)`
This macro setups a function that will setup the test settings for a specific use case. Treat this as if it is a constructor that will construct the tests. 

- `MODERNA_TEARDOWN()`
This macro is run at the end of a successful test. Treat this as if it is a destructor that will destruct tests. 