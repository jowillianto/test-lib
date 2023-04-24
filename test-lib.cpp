#include "test-lib.hpp"

using namespace Test;
// Exception
TestExistException::TestExistException(
  const std::string& testName, const TestCase& testCase
){
  std::stringstream errMsg;
  errMsg << "Test with name "<< testName <<" already exists in test with name ";
  errMsg << testCase.name() << "\n";
  _errMsg   = errMsg.str();
}
const char* TestExistException::what()const noexcept{
  return _errMsg.c_str();
}

// TestCase
TestCase::TestCase(const std::string& testName){
  _testName   = testName;
}
void TestCase::addTest(
  const std::string& testName, const std::function<void()>& func
){
  if(_tests.count(testName) == 0) 
    _tests[testName] = func;
  else
    throw TestExistException(testName, *this);
}
void TestCase::runAll() const{
  std::map<std::string, std::string> errors;
  std::map<std::string, std::string> succeeds;
  
  _printTestHeader();
  for(const auto& [testName, testFunc] : _tests){
    try{
      testFunc();
      succeeds[testName]= "Test done";
      _printTestProgression();
    }
    catch(const std::exception& e){
      errors[testName]  = std::string(e.what());
      _printTestProgression(true);
    }
    catch(const char* e){
      errors[testName]  = std::string(e);
      _printTestProgression(true);
    }
  }
  std::cout<<std::endl<<std::endl;
  _printTestFooter(errors, succeeds);
}

const std::string& TestCase::name()const{
  return _testName;
}
std::string& TestCase::name(){
  return _testName;
}

void TestCase::_printTestHeader() const{
  std::cout<<"Running tests with name : "<<name()<<std::endl;
  std::cout<<"Number of tests : "<<_tests.size()<<std::endl;
  std::cout<<std::endl;
}

void TestCase::_printTestProgression(const bool& err){
  if (err)
    std::cout<<"E";
  else 
    std::cout<<".";
}

void TestCase::_printTestFooter(
  const std::map<std::string, std::string>& errors, 
  const std::map<std::string, std::string>& success
) const{
  std::cout<<"Success Statistic"<<std::endl;
  _printTestSucceeds(success);
  std::cout<<"Error Statistic"<<std::endl;
  _printTestErrors(errors);
  std::cout<<"Test Completed with the following statistics :"<<std::endl;
  std::cout<<"Number of test in total : " << _tests.size()<<std::endl;
  std::cout<<"Number of test succeeded: " << success.size()<<std::endl;
}

void TestCase::_printTestErrors(
  const std::map<std::string, std::string>& errors
){
  for(const auto& [testName, errMsg] : errors){
    std::cout<<"- Error occured in test with name : "<<testName<<std::endl;
    std::cout<<std::endl<<"\t"<<errMsg<<std::endl;
  }
  std::cout<<std::endl;
}

void TestCase::_printTestSucceeds(
  const std::map<std::string, std::string>& succeed
){
  for(const auto& [testName, msg] : succeed){
    std::cout<<"- Test with name : "<<testName<<std::endl;
    std::cout<<"  has been successfully executed";
    std::cout<<std::endl;
    std::cout<<std::endl<<"\t"<<msg<<std::endl;
  }
  std::cout<<std::endl;
}