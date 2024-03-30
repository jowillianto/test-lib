import test_lib;
#include <memory>

template<typename T>
struct Node{
  T value;
  std::unique_ptr<Node> next;
};

template<typename T>
class LinkedList{
  std::unique_ptr<Node<T> > _root;
  public:
    void add_head(T value) {
      _root = std::make_unique<Node<T> >(Node<T>{
        .value = value, 
        .next = std::move(_root)
      });
    }

    void add_tail(T value) {
      // Pointer to root
      std::unique_ptr<Node<T> >* node = &_root;
      while ( *node ) {
        node = &((*node) -> next);
      }
      *node = std::make_unique<Node<T> >(Node<T>{
        .value = value,
        .next = std::move(*node)
      });
    }

    // If pos > size(), will insert at the end.
    void add_at (uint32_t pos, T value) {
      std::unique_ptr<Node<T> >* node = &_root;
      uint32_t current_pos = 0;
      while (*node && current_pos != pos)  {
        current_pos += 1;
        node = &((*node) -> next);
      }
      *node = std::make_unique<Node<T> >(Node<T>{
        .value = value, .next = std::move(*node)
      });
    }

    void delete_node (uint32_t pos) {
      std::unique_ptr<Node<T> >*  node = &_root;
      uint32_t current_pos = 0;
      while (*node && current_pos != pos) {
        current_pos += 1;
        node = &((*node) -> next);
      }
      *node = (*node) ? std::move((*node) -> next) : nullptr;
    }

    T& operator [] (uint32_t pos) {
      std::unique_ptr<Node<T> >*  node = &_root;
      uint32_t current_pos = 0;
      while (*node && current_pos != pos) {
        current_pos += 1;
        node = &((*node) -> next);
      }
      if (*node) return (*node) -> value;
      throw std::bad_variant_access();
    }
    
    uint32_t size() {
      uint32_t ll_size = 0;
      std::unique_ptr<Node<T> >* node = &_root;
      while ( *node ) {
        node = &((*node) -> next);
        ll_size += 1;
      }
      return ll_size;
    }
};

int main(int argc, char** argv){
  if (argc < 2) {
    throw std::bad_variant_access();
  }
  uint32_t fuzz_count = static_cast<uint32_t>(atoi(argv[1]));
  fuzz_count = fuzz_count >= 10 ? fuzz_count : 10;
  auto tester = test_lib::Tester<>{}
    .add_test(
      "fuzz_test", 
      [ fuzz_count ](){
        LinkedList<uint32_t> ll{};
        for (uint32_t i = 0; i < fuzz_count; i += 1){
          if (ll.size() == 0){
            float r = test_lib::random_integer(0, 1);
            uint32_t v = test_lib::random_integer(0, 100);
            if (r == 0){
              ll.add_head(v);
            }
            else {
              ll.add_tail(v);
            }
            test_lib::assert_equal(ll.size(), 1);
            test_lib::assert_equal(ll[0], v);
          }
          else {
            float r = test_lib::random_integer(0, 3);
            uint32_t old_size = ll.size();
            if (r == 0) {
              uint32_t v = test_lib::random_integer(0, 100);
              ll.add_head(v);
              test_lib::assert_equal(ll.size(), old_size + 1);
              test_lib::assert_equal(ll[0], v);
            }
            else if (r == 1) {
              uint32_t v = test_lib::random_integer(0, 100);
              ll.add_tail(v);
              test_lib::assert_equal(ll.size(), old_size + 1);
              test_lib::assert_equal(ll[old_size], v);
            }
            else if (r == 2) {
              uint32_t v = test_lib::random_integer(0, 100);
              uint32_t id = test_lib::random_integer(0, ll.size() - 1);
              ll.add_at(id, v);
              test_lib::assert_equal(ll.size(), old_size + 1);
              test_lib::assert_equal(ll[id], v);
            }
            else if (r == 3){
              uint32_t id = test_lib::random_integer(0, old_size - 1);
              uint32_t value_after_id = 0;
              if (id != old_size - 1)
                value_after_id = ll[id + 1];
              ll.delete_node(id);
              test_lib::assert_equal(ll.size(), old_size - 1);
              if (id != old_size - 1)
                test_lib::assert_equal(ll[id], value_after_id);
            }
          }
        }
      }
    )
    .add_test("add_head", [](){
      LinkedList<uint32_t> ll{};
      uint32_t v = static_cast<uint32_t>(test_lib::random_integer(0, 100));
      ll.add_head(v);
      test_lib::assert_equal(ll.size(), 1);
      test_lib::assert_equal(ll[0], v);
    })
    .add_test("add_tail", [](){
      LinkedList<uint32_t> ll{};
      uint32_t v = static_cast<uint32_t>(test_lib::random_integer(0, 100));
      ll.add_tail(v);
      test_lib::assert_equal(ll.size(), 1);
      test_lib::assert_equal(ll[0], v);
    })
    .add_test("remove_at_0", [](){
      LinkedList<uint32_t> ll{};
      uint32_t v = static_cast<uint32_t>(test_lib::random_integer(0, 100));
      ll.add_head(v);
      ll.delete_node(0);
      test_lib::assert_equal(ll.size(), 0);
    })
    .add_test("multi insert and remove_at_tail", [](){
      LinkedList<uint32_t> ll{};
      uint32_t v = static_cast<uint32_t>(test_lib::random_integer(0, 100));
      ll.add_head(v);
      ll.add_tail(v + 1);
      test_lib::assert_equal(ll[0], v);
      test_lib::assert_equal(ll[1], v + 1);
      ll.add_at(1, v + 2);
      test_lib::assert_equal(ll[1], v + 2);
      test_lib::assert_equal(ll[2], v + 1);
      ll.delete_node(2);
      test_lib::assert_equal(ll[1], v + 2);
      ll.delete_node(0);
      test_lib::assert_equal(ll[0], v + 2);
    });
  auto results = tester.run_all();
  test_lib::print_result(results);
}