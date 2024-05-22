import moderna.test_lib;
#include <memory>
#include <stdexcept>

using namespace moderna;

template <typename T> struct Node {
  T value;
  std::unique_ptr<Node> next;
};

template <typename T> class LinkedList {
  std::unique_ptr<Node<T>> _root;

public:
  void add_head(T value) {
    _root = std::make_unique<Node<T>>(Node<T>{.value = value, .next = std::move(_root)});
  }

  void add_tail(T value) {
    // Pointer to root
    std::unique_ptr<Node<T>> *node = &_root;
    while (*node) {
      node = &((*node)->next);
    }
    *node = std::make_unique<Node<T>>(Node<T>{.value = value, .next = std::move(*node)});
  }

  // If pos > size(), will insert at the end.
  void add_at(int pos, T value) {
    std::unique_ptr<Node<T>> *node = &_root;
    int current_pos = 0;
    while (*node && current_pos != pos) {
      current_pos += 1;
      node = &((*node)->next);
    }
    *node = std::make_unique<Node<T>>(Node<T>{.value = value, .next = std::move(*node)});
  }

  void delete_node(int pos) {
    std::unique_ptr<Node<T>> *node = &_root;
    int current_pos = 0;
    while (*node && current_pos != pos) {
      current_pos += 1;
      node = &((*node)->next);
    }
    *node = (*node) ? std::move((*node)->next) : nullptr;
  }

  T &operator[](int pos) {
    std::unique_ptr<Node<T>> *node = &_root;
    int current_pos = 0;
    while (*node && current_pos != pos) {
      current_pos += 1;
      node = &((*node)->next);
    }
    if (*node) return (*node)->value;
    throw std::out_of_range("");
  }

  int size() {
    int ll_size = 0;
    std::unique_ptr<Node<T>> *node = &_root;
    while (*node) {
      node = &((*node)->next);
      ll_size += 1;
    }
    return ll_size;
  }

  ~LinkedList() {
    // Move out all the unique_ptr
    // This prevents stackoverflow due to recursive calls done from recursively
    // deleting the nodes
    // This slows down the code a little but it works in all cases
    std::unique_ptr<Node<T>> node = std::move(_root);
    // This will remove the node by moving it out of scope.
    while (node) {
      node = std::move(node->next);
    }
  }
};

int main(int argc, char **argv) {
  auto fuzz_count = test_lib::random_integer(static_cast<int>(1e3), static_cast<int>(5e3));
  auto tester = test_lib::Tester<>{"LinkedList Normal Test"}
                  .add_test(
                    "fuzz_test",
                    [fuzz_count]() {
                      LinkedList<int> ll{};
                      for (int i = 0; i < fuzz_count; i += 1) {
                        if (ll.size() == 0) {
                          float r = test_lib::random_integer(0, 1);
                          int v = test_lib::random_integer(0, 100);
                          if (r == 0) {
                            ll.add_head(v);
                          } else {
                            ll.add_tail(v);
                          }
                          test_lib::assert_equal(ll.size(), 1);
                          test_lib::assert_equal(ll[0], v);
                        } else {
                          float r = test_lib::random_integer(0, 3);
                          int old_size = ll.size();
                          if (r == 0) {
                            int v = test_lib::random_integer(0, 100);
                            ll.add_head(v);
                            test_lib::assert_equal(ll.size(), old_size + 1);
                            test_lib::assert_equal(ll[0], v);
                          } else if (r == 1) {
                            int v = test_lib::random_integer(0, 100);
                            ll.add_tail(v);
                            test_lib::assert_equal(ll.size(), old_size + 1);
                            test_lib::assert_equal(ll[old_size], v);
                          } else if (r == 2) {
                            int v = test_lib::random_integer(0, 100);
                            int id = test_lib::random_integer(0, ll.size() - 1);
                            ll.add_at(id, v);
                            test_lib::assert_equal(ll.size(), old_size + 1);
                            test_lib::assert_equal(ll[id], v);
                          } else if (r == 3) {
                            int id = test_lib::random_integer(0, old_size - 1);
                            int value_after_id = 0;
                            if (id != old_size - 1) value_after_id = ll[id + 1];
                            ll.delete_node(id);
                            test_lib::assert_equal(ll.size(), old_size - 1);
                            if (id != old_size - 1) test_lib::assert_equal(ll[id], value_after_id);
                          }
                        }
                      }
                    }
                  )
                  .add_test(
                    "add_head",
                    []() {
                      LinkedList<int> ll{};
                      int v = static_cast<int>(test_lib::random_integer(0, 100));
                      ll.add_head(v);
                      test_lib::assert_equal(ll.size(), 1);
                      test_lib::assert_equal(ll[0], v);
                    }
                  )
                  .add_test(
                    "add_tail",
                    []() {
                      LinkedList<int> ll{};
                      int v = static_cast<int>(test_lib::random_integer(0, 100));
                      ll.add_tail(v);
                      test_lib::assert_equal(ll.size(), 1);
                      test_lib::assert_equal(ll[0], v);
                    }
                  )
                  .add_test(
                    "remove_at_0",
                    []() {
                      LinkedList<int> ll{};
                      int v = static_cast<int>(test_lib::random_integer(0, 100));
                      ll.add_head(v);
                      ll.delete_node(0);
                      test_lib::assert_equal(ll.size(), 0);
                    }
                  )
                  .add_test("multi insert and remove_at_tail", []() {
                    LinkedList<int> ll{};
                    int v = static_cast<int>(test_lib::random_integer(0, 100));
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
  tester.run_all();
  tester.print_or_exit();
}