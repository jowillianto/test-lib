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

#define MODERNA_SETUP() \
  namespace moderna::test_lib { \
    struct moderna_setup { \
      moderna_setup(); \
    }; \
  } \
  moderna::test_lib::moderna_setup setuper; \
  moderna::test_lib::moderna_setup::moderna_setup()
