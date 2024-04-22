#include <optional>

int main() {
  struct X{
    std::optional<size_t> x;
    size_t mod_x() const {
      if (!x.has_value()){
        x = 10;
      }
      return x.value();
    }
  } lol;
}