#include "testcase.h"

namespace unittests
{

TestCase::TestCase(const char* name, TestLogger* logger) :
  logger_(logger), name_(name)
{
}

TestCase::~TestCase()
{
}

bool TestCase::run()
{
  return true;
}

void TestCase::init()
{
}

void TestCase::cleanup()
{
}

void TestCase::destroy()
{
}

} // namespace

/* vim: set cindent sw=2 expandtab : */

