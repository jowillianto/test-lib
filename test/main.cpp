#include <iostream>
#include <format>
#include <random>
#include <thread>
#include <chrono>

import test_lib;

int main(){
  test_lib::Tester tester;
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<uint32_t> distrib(100, 5000);
  for (uint32_t i = 0; i < distrib(gen); i += 1){
    tester.add_test(test_lib::TestConfig{
      std::format("print random string {}", std::to_string(i)), 
      [i, &gen, &distrib](){
        std::this_thread::sleep_for(
          std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::milliseconds(distrib(gen))
          )
        );
        std::cout<<std::format(
          "{}. {}\n", std::to_string(i), test_lib::random_string(10)
        );
      }
    });
  }
  tester.run_all();
  tester.run_test("print random string 10");
}