#ifndef UNITTESTS_TESTSUITE_H__
#define UNITTESTS_TESTSUITE_H__

#include <vector>
#include "testlogger.h"
#include "testcase.h"

namespace unittests
{

/**
  \class TestSuite testsuite.h "ut/testsuite.h"
  \ingroup Unittests
  \brief The TestSuite class represent a suite of test cases to be run.

  The TestSuite is constructed using a test logger, which will be passed to all test cases included in this suite.
  The test suite can be seen as an array of test cases, where each test can be accessed through it's index in the array.
  */
class TestSuite
{
public:
  /**
    \brief Constructs a testsuite which will log the test results to the given logger

    The logger is going to be passed to all test cases included in this suite for logging of their results.
    \param logger - The logger which will log the test results
    */
  TestSuite(TestLogger* logger);
  virtual ~TestSuite();

  /**
    \brief Runs this test suite
    */
  void run();

  /**
    \brief returns the number of tests included in this suite
    \return Returns the number of tests included in this suite
    */
  virtual int test_count();

  /**
    \brief Returns the test case at index passed in as a parameter

    The TestSuite can be thought of as an array of test cases, this method exposes this functionality by providing access to the test cases by index

    \param index - The index of the test case we want access to
    \return Returns the test case at the index passed in as the parameter
    */
  virtual TestCase* operator[](int index);
protected:
  virtual void load_cases() = 0;
  /**
    \brief Adds a new test case of type T to the test cases stored by this suite
    */
  template <typename T>
  void add_test_case(const char* name)
  {
    cases_.push_back(new T(logger_));
  }
private:
  virtual void init() {}
  virtual void destroy() {}
  TestLogger* logger_;
  std::vector<TestCase*> cases_;
};

} // namespace

#endif // UNITTESTS_TESTSUITE_H__

/* vim: set cindent sw=2 expandtab : */

