#define MODERNA_ADD_TEST(name) \
  struct name { \
    void operator()() const; \
  }; \
  struct name##_initiator { \
    name##_initiator() { \
      moderna::test_lib::add_test(name{}); \
    } \
  }; \
  static name##_initiator name##_var{}; \
  void name::operator()() const
