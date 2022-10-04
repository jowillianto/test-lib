#include "../test-lib.hpp"
#include <cassert>

Test::TestCase test("TestCase test");

int main(){
  test.addTest("Add normal test to suite", [](){
    int x   = 0;
    int y   = 1;
    int z   = 2;
    int xyz = x * y * z;
  });
  test.addTest("Add error test to suite", [](){
    int x   = 0;
    int y   = 1;
    throw "Lol test failed";
  });
  test.runAll();
}