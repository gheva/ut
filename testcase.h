#ifndef UNITTESTS_TESTCASE_H__
#define UNITTESTS_TESTCASE_H__

#include <string>
#include "assertionfailed.h"
#include "testlogger.h"
namespace unittests
{

/**
  \class TestCase testcase.h "ut/testcase.h"
  \ingroup Unittests
  \brief This class represents a single test case.

  The test cases are stored by the TestSuite which passes it's logger to the constructor of the test cases.
  Each test case has a name, which is used for reporting purposes.
  */
class TestCase
{
public:
  TestCase(const char* name, TestLogger* logger);
  virtual ~TestCase();
  /**
    \brief Run this test case

    Subclasses are expected to implement this method, which should return true if the test passed.
    Assertions should be evaluated through the call to assert_eq, which will throw an exception if an assertion fails. The TestSuite will catch all such exceptions and mark the test as failed.
    \return Returns true if the test passed, false otherwise.
    */
  virtual bool run();

  /**
    \brief Returns the name of this suite
    \return The string representation of this suite's name
    */
  std::string get_name() { return name_; }

protected:
  /**
    \brief Evaluate whether or not the expected and the actual are the same, throw an exception if not.

    Assertion in the unittests are evaluated using this method, which will throw an AssertionFailed exception if the assertion is failing. This exception is caught by the TestSuite, and reported.

    \param val - The found value
    \param expected - The expected value
    \param file - The file name containing the failing assertion
    \param line -  The line in which the failing assertion happens
    */
  template <typename T>
  void assert_eq(T val, T expected, const char* file, int line)
  {
    if (val == expected)
    {
      return;
    }

    AssertionFailed* f = new AssertionFailed("Assert equal failed: At ");
    AssertionFailed& failure(*f);
    failure << file << ':' << line;
    failure << " - Expected: " << expected << " Found: " << val;
    throw f;
  }

  virtual void init();
  virtual void destroy();
  virtual void cleanup();
  TestLogger* logger_;
private:
  std::string name_;
};

} // namespace

#endif // UNITTESTS_TESTCASE_H__

/* vim: set cindent sw=2 expandtab : */

