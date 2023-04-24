#include <string>
#include <map>
#include <exception>
#include <sstream>
#include <iostream>
#include <functional>

#pragma once

namespace Test{
  class TestCase{
    public:
      TestCase(const std::string& testName);
      void addTest(
        const std::string& testName, 
        const std::function<void()>& func
      );
      void runAll() const;
      
      // Name
      const std::string& name()const;
      std::string& name();

    private:
      std::map<std::string, std::function<void()>> _tests;
      // Private Function for use
      void _printTestHeader() const;
      void _printTestFooter(
        const std::map<std::string, std::string>& errors, 
        const std::map<std::string, std::string>& success
      ) const;
      
      static void _printTestProgression(const bool& err = false);

      static void _printTestErrors(
        const std::map<std::string, std::string>& errors
      );
      static void _printTestSucceeds(
        const std::map<std::string, std::string>& succeed
      );
      std::string _testName;
  };

  class TestExistException : public std::exception{
    public:
      TestExistException(const std::string& testName, const TestCase& testCase);
      const char* what()const noexcept;
    private:
      std::string _errMsg;
  };
}