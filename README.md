# Test Lib
A Simple and Light C++20 modules based C++ testing library. 

## Example Usage
```cpp
import test_lib
auto tester = test_lib::Tester();
tester.add(test_lib::TestConfig{
  "<your_test_name>", 
  [](){
    /*
      Function to test your implementation of something.
    */
  }
})
```