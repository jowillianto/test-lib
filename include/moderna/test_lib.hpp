#define MODERNA_ADD_TEST(name) \
  struct name { \
    void operator()() const; \
  }; \
  struct name##_initiator { \
    name##_initiator() { \
      moderna::test_lib::get_test_context().tests.add_test(name{}); \
    } \
  }; \
  static name##_initiator name##_var{}; \
  void name::operator()() const

#define MODERNA_SETUP(argc, argv) \
  template <> struct moderna::test_lib::test_setup<moderna::test_lib::setup_mode::SET_UP> { \
    test_setup() { \
      moderna::test_lib::get_test_context().add_setup(set_up); \
    } \
    static void set_up(int argc, const char **argv); \
  }; \
  static moderna::test_lib::test_setup<moderna::test_lib::setup_mode::SET_UP> \
    __moderna_test_lib_setup; \
  void moderna::test_lib::test_setup<moderna::test_lib::setup_mode::SET_UP>::set_up( \
    int argc, const char **argv \
  )

#define MODERNA_TEARDOWN() \
  template <> struct moderna::test_lib::test_setup<moderna::test_lib::setup_mode::TEAR_DOWN> { \
    test_setup() { \
      moderna::test_lib::get_test_context().add_teardown(tear_down); \
    } \
    static void tear_down(); \
  }; \
  static moderna::test_lib::test_setup<moderna::test_lib::setup_mode::TEAR_DOWN> \
    __moderna_test_lib_teardown; \
  void moderna::test_lib::test_setup<moderna::test_lib::setup_mode::TEAR_DOWN>::tear_down()
