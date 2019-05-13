#ifndef UNITTESTS_TESTRUNNER_H__
#define UNITTESTS_TESTRUNNER_H__

#include <map>
#include <string>
#include "testlogger.h"
#include "testsuite.h"

namespace unittests
{

/**
  \class TestRunner testrunner.h "ut/testrunner.h"
  \ingroup Unittests
  \brief This class run a set of named TestSuites, or a single one, by it's name.
  */
class TestRunner
{
public:
  /**
    \brief constructs a new TestRunner which will log to the provided TestLogger.
    \param logger - A TestLogger instance used for logging test results
    */
  TestRunner(TestLogger* logger);
  virtual ~TestRunner();
  /**
    \brief Run a single suite named `name`.
    \param name - The name of the suite to run
    */
  void run(std::string name);

  /**
    \brief Runs all the suites which this runner holds
    */
  void run();

  /**
    \brief Adds a suite of tests to this test runner

    This method is templated on the TestSuite subtype, which will allow us to instantiate different TestSuite objects, passing the type in as a "parameter"

    \param name - The name by which this suite should be known
    */
  template <typename T>
  void add_suite(const char* name)
  {
    T* suite = new T(logger_);
    suites_[name] = suite;
  }
private:
  TestLogger* logger_;
  std::map<std::string, TestSuite*> suites_;
};

} // namespace

#endif // UNITTESTS_TESTRUNNER_H__

/* vim: set cindent sw=2 expandtab : */

