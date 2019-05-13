#include "testrunner.h"

namespace unittests
{

TestRunner::TestRunner(TestLogger* logger) :
  logger_(logger)
{
}

TestRunner::~TestRunner()
{
  std::map<std::string, TestSuite*>::iterator iter;
  for (iter = suites_.begin(); iter != suites_.end(); ++iter)
  {
    delete iter->second;
  }
}

void TestRunner::run()
{
  std::map<std::string, TestSuite*>::iterator iter;
  for (iter = suites_.begin(); iter != suites_.end(); ++iter)
  {
    iter->second->run();
  }
}

void TestRunner::run(std::string name)
{
  TestSuite* suite = suites_[name];
  if (suite)
  {
    suite->run();
  }
}

} // namespace

/* vim: set cindent sw=2 expandtab : */

