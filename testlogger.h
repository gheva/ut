#ifndef UNITTESTS_TESTLOGGER_H__
#define UNITTESTS_TESTLOGGER_H__

#include <string>
#include <cstdarg>

namespace unittests
{

/**
  \class TestLogger testlogger.h "ut/testlogger.h"
  \ingroup Unittests

  \brief This is an abstract class representing a logger which can be used for logging test cases.
  */
class TestLogger
{
public:
  /**
    \brief Log a single line of text.
    \param line - The line of code to be logged.
    */
  virtual void log_line(const char* line) = 0;

  /**
    \brief Log a single line of text.
    \param line - The line of code to be logged.
    */
  virtual void log_line(std::string& line) = 0;

  /**
    \brief Log a formatted message.
    \param fmt - The format to be used for formatting the message
    \param ap - The variable arguments to be used as arguments to the format
    */
  virtual void vlogf(const char* fmt, va_list ap) = 0;

  /**
    \brief Log a formatted message.
    \param fmt - The format to be used for formatting the message
    \param ... - The variable arguments to be used as arguments to the format
    */
  virtual void logf(const char* fmt, ...) = 0;
};

} // namespace

#endif // UNITTESTS_TESTLOGGER_H__

/* vim: set cindent sw=2 expandtab : */

