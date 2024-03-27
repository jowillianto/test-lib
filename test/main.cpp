#include <chrono>
#include <iostream>
#include <thread>
#include <format>
import test_lib;

int main(){
  test_lib::Tester tester;
  for (uint32_t i = 0; i < test_lib::random_integer(100, 5000); i += 1){
    tester.add_test(
      std::format("print random string {}", std::to_string(i)), 
      [i](){
        std::this_thread::sleep_for(
          std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::milliseconds(test_lib::random_integer(100, 5000))
          )
        );
        std::cout<<std::format(
          "{}. {}\n", std::to_string(i), test_lib::random_string(10)
        );
      }
    );
  }
  tester.run_all();
  tester.run_test("print random string 10");
}