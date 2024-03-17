
#include "./random.hpp"
#include <random>
#include <string>

using namespace Test;

// Specialization
template<>
std::string Test::generate_random(uint32_t length){
  auto randomString = std::string();
  auto device = std::random_device{};
  auto generator = std::mt19937{device};
  auto distribution = std::uniform_int_distribution<unsigned char>{
    32, 126
  };
  randomString.reserve(length);
  for (uint32_t i = 0; i < length; i += 1)
    randomString += distribution(generator);
  return randomString;
}