import moderna.test_lib;
#include <chrono>
#include <future>
#include <map>
#include <mutex>
#include <optional>
#include <shared_mutex>

using namespace moderna;
template <typename F, typename R, typename... Args>
concept invocable_r = requires(F f, Args &&...args) {
  { f(std::forward<Args>(args)...) } -> std::convertible_to<R>;
};

template <typename K, typename T> class Cache {
  struct CacheEntry {
    std::optional<T> data;
    std::mutex lock;
  };
  std::map<K, CacheEntry> _cache;
  // Locks key insertion (Data inside map could mutate without having the lock
  // _cacheLock)
  std::shared_mutex _cacheLock;

public:
  template <invocable_r<T> F> const T &get_or_insert(const K &key, F gen_function) {
    std::shared_lock read_lock{_cacheLock};
    if (_cache.contains(key)) {
      read_lock.unlock();
      CacheEntry &entry = _cache[key];
      std::unique_lock entry_read_lock{entry.lock};
      return entry.data.value();
    }
    read_lock.unlock();
    std::unique_lock write_lock{_cacheLock};
    if (_cache.contains(key)) {
      write_lock.unlock();
      CacheEntry &entry = _cache[key];
      std::unique_lock entry_write_lock{entry.lock};
      return entry.data.value();
    }
    CacheEntry &entry = _cache[key];
    std::unique_lock entry_lock{entry.lock};
    write_lock.unlock();
    entry.data = gen_function();
    return entry.data.value();
  }
};

int main() {
  Cache<std::string, uint32_t> cache;
  auto tester = test_lib::Tester<>{"Multithread Cache Test"}.add_test(
    "simultaneous access from two threads",
    [&]() {
      std::thread([&]() {
        cache.get_or_insert("a", []() {
          std::this_thread::sleep_for(
            std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(500))
          );
          return static_cast<uint32_t>(2);
        });
      }).detach();
      std::thread([&]() {
        cache.get_or_insert("a", []() {
          throw std::bad_exception();
          return static_cast<uint32_t>(2);
        });
      }).detach();
      auto status =
        std::async(std::launch::async, [&]() {
          cache.get_or_insert("c", []() {
            std::this_thread::sleep_for(
              std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(500))
            );
            return static_cast<uint32_t>(2);
          });
        }).wait_for(std::chrono::milliseconds(550));
      if (status == std::future_status::timeout) throw std::bad_exception();
    }
  ); 
  tester.run_all();
  tester.print_or_exit();
}