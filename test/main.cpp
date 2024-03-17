#include <iostream>
#include <format>

import test_lib;

int main(){
  test_lib::Tester tester;
  for (uint32_t i = 0; i < 100; i += 1){
    tester.add_test(test_lib::TestConfig{
      std::format("print random string {}", std::to_string(i)), 
      [i](){
        std::cout<<std::format(
          "{}. {}\n", std::to_string(i), test_lib::random_string(10)
        );
      }
    });
  }
  tester.run_all();
  tester.run_test("print random string 10");
}