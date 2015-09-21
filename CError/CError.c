#include "CError.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>


static void _error(int process_errno, const char* format, va_list ap)
{
    char buf[CERROR_MAXLINE+1];
    int errno_save, n;
 
    errno_save = errno;
    vsnprintf(buf, CERROR_MAXLINE, format, ap);

    if (process_errno) {
        n = strlen(buf);
        snprintf(buf+n, CERROR_MAXLINE-n, ": %s", strerror(errno_save));
    }

    strcat(buf, "\n");

    /* The function might be updated to push syslog messages instead of
       stderr. The code should be put here */

    fflush(stdout);
    fputs(buf, stderr);
    fflush(stderr);
}

void err_sys(const char* format, ...)
{
    va_list ap;

    va_start(ap, format);
    _error(1, format, ap);
    va_end(ap);

    exit(EXIT_FAILURE);
}

void err_ret(const char* format, ...)
{
    va_list ap;

    va_start(ap, format);
    _error(1, format, ap);
    va_end(ap);

    return;
}

void err_quit(const char* format, ...)
{
    va_list ap;

    va_start(ap, format);
    _error(0, format, ap);
    va_end(ap);

    exit(EXIT_FAILURE);
}

void err_msg(const char* format, ...)
{
    va_list ap;

    va_start(ap, format);
    _error(0, format, ap);
    va_end(ap);

    return;
}
