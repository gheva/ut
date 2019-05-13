#ifndef UT_UNITTESTS_H__
#define UT_UNITTESTS_H__
/**
  \defgroup Unittests Unittests
  \brief This module contains a simple and easy to use unittest framework.

  The Framework consists of the following entities:
  \li unittests::TestRunner - Which will be running the tests. The test runner hlds one or more TestSuites which will be run based on the command line arguments passed to the runner.
  \li unittests::TestSuite - which is a grouping of tests, this is the lowest resolution of test running, we can either run all tests, or all tests in a suite, there is no way to run a single test case
  \li unittests::TestCase - this is a single test, which can only be run from the context of a suite

  All test results are logged by the logger which is held by the TestRunner and passed to the TestSuite instances held by the runner, which will in turn pass the logger to the individual TestCase instances in the suite. This allows the runner to decide where and how to log the test results.

Creating a testing application:
To create a testing application you will need to instantiate a TestRunner with a TestLogger, then add suites to the runner. The suites are responsible of adding test cases to themselves.

In the file main.cpp
\code
#include "ut/unittests.h"
using namespace unittests;
int main(int argc, char** argv)
{
  StdoutLogger logger;
  TestRunner runner(&logger);
  // Add the ValueTests suite to the runner
  CALL_ADD_TO_RUNNER(ValueTests, &runner);
}
\endcode

In a suite header file:
\code
#include "ut/unittests.h"

namespace unittests
{

DECLARE_SUITE(ValueTests);

} // end of namespace

// This declaration HAS to be outside of the unittests namespace
DECLARE_ADD_TO_RUNNER(ValueTests);
\endcode

In the suite C++ file:
In the C++ file we need to do a few things:
\li declare TestCases. This could be done in other files and then included here.
\li define the TestSuite
\li make sure TestCases are added to the TestSuite

\code
namespace unittests {
// Declare and define a test case
TEST_CASE(value_test_bool)
virtual bool run()
{
// Test code goes here
return true;
}
END_CASE;

// Methods for the TestSuite which need to be implemented
void ValueTests::init()
{
}

void ValueTests::destroy()
{
}

void ValueTests::load_cases()
{
  ADD_TEST_CASE(value_test_bool)
}

} // end of namespace

// This HAS to be outside of the unittests namespace
DEFINE_ADD_TO_RUNNER(ValueTests);
\endcode


  */

/**
  \file unittests.h
  \ingroup Unittests
  \brief This file should be included for creating and running unittests using our framework, it contains helper macros to speed up test creation.
  */

#include "assertionfailed.h"
#include "stdoutlogger.h"
#include "testcase.h"
#include "testlogger.h"
#include "testrunner.h"
#include "testsuite.h"

/**
  \def ASSERT_EQ(found, expected)
  \brief within a TestCase this macro expands to a call to assert_eq with the file and line populated by the compiler.
  \param found - The value as found when running the tests
  \param expected - The expected value
  \sa TestCase::assert_eq
  */
#define ASSERT_EQ(found, expected) assert_eq(found, expected, __FILE__, __LINE__)

/**
  \def ASSERT_TRUE(value)
  \brief within a TestCase this macro expands to evaluate that the passed in value will evaluate to true
  \param value - The value as found when running the tests
  \sa TestCase::assert_eq
  */
#define ASSERT_TRUE(value) assert_eq(static_cast<bool>(value), true, __FILE__, __LINE__)

/**
  \def ASSERT_FALSE(value)
  \brief within a TestCase this macro expands to evaluate that the passed in value will evaluate to false
  \param value - The value as found when running the tests
  \sa TestCase::assert_eq
  */
#define ASSERT_FALSE(value) assert_eq(static_cast<bool>(value), false, __FILE__, __LINE__)


/**
  \def TEST_CASE(name)
  \brief Start the definition of a test case

  A test case begins with a call to TEST_CASE followed by a definition of the run method, followed by a call to END_CASE.

  For example, the following code will create a class named SiteAddingTester, which is a subclass of the TestCase class, and can later be added to a suite

  \code
  TEST_CASE(SiteAddingTester)
  public bool run()
  {
  // implement the test here
  }
  END_CASE;
  \endcode
  */
#define TEST_CASE(name) \
class name : public TestCase { \
public: \
  name(TestLogger* logger) : TestCase(#name, logger) { init(); } \
  virtual ~name() { destroy(); } \

/**
  \def END_CASE
  \brief This macro should be used to denote the end of a TestCase
  */
#define END_CASE }

/**
  \def ADD_TEST_SUITE(name)
  \brief Adds a TestSuite to the TestRunner

  The TestSuite's class name should be the name passed i as a parameter.
  \param name - The class name of the test suite
  */
#define ADD_TEST_SUITE(name) add_suite<unittests::name>(#name)

/**
  \def ADD_TEST_CASE(name)
  \brief Adds a TestCase to a TestSuite

  The TestCase's class name must be the name passed in as a parameter
  \param name - The class name of the TestCase to be added
  */
#define ADD_TEST_CASE(name) add_test_case<unittests::name>(#name)

/**
  \def DECLARE_SUITE(name)
  \brief Declares a compilable and linkable TestSuite.

  Users must define the protected methods, specifically the load_cases needs to include calls to ADD_TEST_CASE for the cases included in this suite.
  \param name - The class name for the suite
  */
#define DECLARE_SUITE(name) \
class name : public TestSuite {\
public: \
  name(TestLogger* logger) : TestSuite(logger) {} \
  virtual ~name() { destroy(); } \
protected: \
  virtual void load_cases(); \
  virtual void init(); \
  virtual void destroy(); \
}

/**
  \def DEFINE_ADD_TO_RUNNER(suite)
  \brief Expands to a function definition which will add a suite with the given name to a passed in TestRunner

  \sa DECLARE_ADD_TO_RUNNER
  */
#define DEFINE_ADD_TO_RUNNER(suite) \
void suite##_add_to_runner(unittests::TestRunner* runner) { \
  runner->ADD_TEST_SUITE(suite); }

/**
  \def DECLARE_ADD_TO_RUNNER(suite)
  \brief Expands to a function declaration which will add a suite with the given name to a passed in TestRunner

  \sa DEFINE_ADD_TO_RUNNER
  */
#define DECLARE_ADD_TO_RUNNER(suite) \
void suite##_add_to_runner(unittests::TestRunner* runner)

/**
  \def CALL_ADD_TO_RUNNER(suite, runner)
  \brief expands to a call to the function declared by DECLARE_ADD_TO_RUNNER(suite)
  */
#define CALL_ADD_TO_RUNNER(suite, runner) \
suite##_add_to_runner(runner)

#endif // UT_UNITTESTS_H__

/* vim: set cindent sw=2 expandtab : */

