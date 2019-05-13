#ifndef UNITTESTS_STDOUTLOGGER_H__
#define UNITTESTS_STDOUTLOGGER_H__

#include <string>
#include "testlogger.h"

namespace unittests
{

/**
  \class StdoutLogger stdoutlogger.h "ut/stdoutlogger.h"
  \ingroup Unittests
  \brief This class is used for logging test results to stdout
  \sa TestLogger
  */
class StdoutLogger : public TestLogger
{
public:
  virtual void log_line(const char* line);
  virtual void log_line(std::string& line);
  virtual void vlogf(const char* fmt, va_list ap);
  virtual void logf(const char* fmt, ...);
};

} // namespace

#endif // UNITTESTS_STDOUTLOGGER_H__

/* vim: set cindent sw=2 expandtab : */

