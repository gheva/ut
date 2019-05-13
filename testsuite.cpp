#include "testsuite.h"

namespace unittests
{

TestSuite::TestSuite(TestLogger* logger) : logger_(logger)
{
}

TestSuite::~TestSuite()
{
  for (int i = 0; i < cases_.size(); ++i)
  {
    delete cases_[i];
  }
}

int TestSuite::test_count()
{
  return cases_.size();
}

TestCase* TestSuite::operator[](int index)
{
  return cases_[index];
}

void TestSuite::run()
{
  load_cases();
  int count(test_count());

  init();

  for (int index(0); index < count; ++index)
  {
    TestCase* test = (*this)[index];
    if (test == NULL)
    {
      continue;
    }
    logger_->logf("Running %s\n", test->get_name().c_str());
    try
    {
      test->run();
    }
    catch (AssertionFailed* e)
    {
      logger_->logf("%s\n", e->get_info().c_str());
      delete e;
      goto failure;
    }
    catch (...)
    {
      logger_->logf("An un handled exception was caught while running %s\n",
        test->get_name().c_str());
    }
    logger_->logf("Success\n");
    continue;
failure:
    logger_->logf("Failed\n");
  }
  destroy();
}

} // namespace

/* vim: set cindent sw=2 expandtab : */

