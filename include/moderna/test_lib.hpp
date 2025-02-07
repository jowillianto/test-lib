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

#define MODERNA_SETUP(argc, argv) \
  template <> struct moderna::test_lib::test_setup<moderna::test_lib::setup_mode::SET_UP> { \
    static void set_up(int argc, const char **argv); \
  }; \
  void moderna::test_lib::test_setup<moderna::test_lib::setup_mode::SET_UP>::set_up( \
    int argc, const char **argv \
  )

#define MODERNA_TEARDOWN() \
  template <> struct moderna::test_lib::test_setup<moderna::test_lib::setup_mode::TEAR_DOWN> { \
    static void tear_down(); \
  }; \
  void moderna::test_lib::test_setup<moderna::test_lib::setup_mode::TEAR_DOWN>::tear_down()
