#include <string>
#include <map>
#include <exception>
#include <functional>

#pragma once

namespace Test{
  class TestCase{
    public:
      TestCase(const std::string& test_name);
      void add_test(
        const std::string& test_name, 
        const std::function<void()>& func
      );
      void run_all() const;
      
      // name
      const std::string& name()const;
      std::string& name();

    private:
      std::map<std::string, std::function<void()>> _tests;
      // private function for use
      void _print_test_header() const;
      void _print_test_footer(
        const std::map<std::string, std::string>& errors, 
        const std::map<std::string, std::string>& success
      ) const;
      
      static void _print_test_progression(const bool& err = false);

      static void _print_test_errors(
        const std::map<std::string, std::string>& errors
      );
      static void _print_test_succeeds(
        const std::map<std::string, std::string>& succeed
      );
      std::string _test_name;
  };

  class TestExistException : public std::exception{
    public:
      TestExistException(const std::string& test_name, const TestCase& TestCase);
      const char* what()const noexcept;
    private:
      std::string _err_msg;
  };
}