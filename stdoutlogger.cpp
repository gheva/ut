#include "stdoutlogger.h"

namespace unittests
{

void StdoutLogger::log_line(const char* line)
{
  fprintf(stdout, "%s\n", line);
}

void StdoutLogger::log_line(std::string& line)
{
  fprintf(stdout, "%s\n", line.c_str());
}

void StdoutLogger::vlogf(const char* fmt, va_list ap)
{
  vfprintf(stdout, fmt, ap);
}

void StdoutLogger::logf(const char* fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stdout, fmt, ap);
  va_end(ap);
}

} // namespace

/* vim: set cindent sw=2 expandtab : */

