
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "log.h"

void
log_init(int *argc, char ***argv, int logopt, int logfac)
{
  char *progname;
  
  progname = (progname = strrchr((*argv)[0], '/')) ? progname+1 : (*argv)[0];
  openlog(progname, logopt, logfac);
}

void
log_raw(int priority, const char *format, ...)
{
  char *prefix;
  FILE *out;
  va_list args;

  va_start(args, format);

  out=stderr;
  switch (priority) {
    case LOG_EMERG:
      prefix="<EMERG>";
      break;
    case LOG_ALERT:
      prefix="<ALERT>";
      break;
    case LOG_ERR:
      prefix="<ERR>  ";
      break;
    case LOG_WARNING:
      prefix="<WARN> ";
      break;
    case LOG_NOTICE:
      prefix="<NOTE> ";
      out=stdout;
      break;
    case LOG_INFO:
      prefix="<INFO> ";
      out=stdout;
      break;
    case LOG_DEBUG:
      prefix="<DEBUG>";
      out=stdout;
      break;
    default:
      prefix="<INFO> ";
      out=stdout;
  }
  
  vsyslog(priority, format, args);
  if (out) {
    (void)fprintf(out, "%s ", prefix);
    (void)vfprintf(out, format, args);
    (void)fprintf(out, "\n");
  }
  va_end(args);
}

