# Test Lib
A Simple and Light C++23 modules based C++ testing library. 

## Example Usage
```cpp
import moderna.test_lib;

namespace test_lib = moderna::test_lib;
#include <moderna/test_lib/macros.hpp>

MODERNA_ADD_TEST(some_name) {
  /*
    Do something over here
  */
}
```
The above will add the test into the test list. Compiling this file using cmake with `moderna_add_test` will result in the test being added and run automatically. 
