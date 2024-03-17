#pragma once

namespace Test{
  template<typename RandomType, typename ...Args>
  RandomType generate_random(Args ...args);
}