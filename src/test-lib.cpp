#include "test-lib.hpp"
#include <sstream>
#include <iostream>

using namespace Test;
// Exception
TestExistException::TestExistException(
  const std::string& test_name, const TestCase& test_case
){
  std::stringstream err_msg;
  err_msg << "test with name "<< test_name <<" already exists in test with name ";
  err_msg << test_case.name() << "\n";
  _err_msg   = err_msg.str();
}
const char* TestExistException::what()const noexcept{
  return _err_msg.c_str();
}

// TestCase
TestCase::TestCase(const std::string& test_name){
  _test_name = test_name;
}
void TestCase::add_test(
  const std::string& test_name, const std::function<void()>& func
){
  if(_tests.count(test_name) == 0) 
    _tests[test_name] = func;
  else
    throw TestExistException(test_name, *this);
}
void TestCase::run_all() const{
  std::map<std::string, std::string> errors;
  std::map<std::string, std::string> succeeds;
  
  _print_test_header();
  for(const auto& [test_name, test_func] : _tests){
    try{
      test_func();
      succeeds[test_name]= "test done";
      _print_test_progression();
    }
    catch(const std::exception& e){
      errors[test_name]  = std::string(e.what());
      _print_test_progression(true);
    }
    catch(const char* e){
      errors[test_name]  = std::string(e);
      _print_test_progression(true);
    }
    catch(const std::string& e){
      errors[test_name]  = e;
      _print_test_progression(true);
    }
  }
  std::cout<<std::endl<<std::endl;
  _print_test_footer(errors, succeeds);
}

const std::string& TestCase::name()const{
  return _test_name;
}
std::string& TestCase::name(){
  return _test_name;
}

void TestCase::_print_test_header() const{
  std::cout<<"running tests with name : "<<name()<<std::endl;
  std::cout<<"number of tests : "<<_tests.size()<<std::endl;
  std::cout<<std::endl;
}

void TestCase::_print_test_progression(const bool& err){
  if (err)
    std::cout<<"e";
  else 
    std::cout<<".";
}

void TestCase::_print_test_footer(
  const std::map<std::string, std::string>& errors, 
  const std::map<std::string, std::string>& success
) const{
  std::cout<<"success statistic"<<std::endl;
  _print_test_succeeds(success);
  std::cout<<"error statistic"<<std::endl;
  _print_test_errors(errors);
  std::cout<<"test completed with the following statistics :"<<std::endl;
  std::cout<<"number of test in total : " << _tests.size()<<std::endl;
  std::cout<<"number of test succeeded: " << success.size()<<std::endl;
}

void TestCase::_print_test_errors(
  const std::map<std::string, std::string>& errors
){
  for(const auto& [test_name, err_msg] : errors){
    std::cout<<"- error occured in test with name : "<<test_name<<std::endl;
    std::cout<<std::endl<<"\t"<<err_msg<<std::endl;
  }
  std::cout<<std::endl;
}

void TestCase::_print_test_succeeds(
  const std::map<std::string, std::string>& succeed
){
  for(const auto& [test_name, msg] : succeed){
    std::cout<<"- test with name : "<<test_name<<std::endl;
    std::cout<<"  has been successfully executed";
    std::cout<<std::endl;
    std::cout<<std::endl<<"\t"<<msg<<std::endl;
  }
  std::cout<<std::endl;
}