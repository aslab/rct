/*
 * @author Francisco J. Arjonilla
 * Last Change: Thu Feb 17 06:00 PM 2011 C
 */
#include <stdarg.h>
#include <stdio.h>
#include "Exception.h"

/** \class Exception Utility class for outputting the cause of an exception.
 */

Exception::Exception(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  vsnprintf(msg, sizeof(msg), format, args);
  va_end(args);
}

ostream &operator<<(ostream &out, const Exception& ex)
{
  out << ex.msg;
  return out;
}
