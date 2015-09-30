#include "CHelper.h"

#include <errno.h>
#include <limits.h>

long Strtol(const char *restrict str, int base)
{
    long r;
    char *endptr;

    errno = 0;
    r = strtol(str, &endptr, base);

    if ((errno == ERANGE && (r == LONG_MAX || r == LONG_MIN)) || (errno != 0 && r == 0))
        err_sys("error converting string [%s] to long", str);

    if (endptr == str)
        err_quit("error converting string [%s] to long: no digits were found", str);

    if (*endptr != '\0')
        err_quit("error converting string [%s] to long: string contains unconvertable characters", str);

    return r;
}

long Strtol10(const char *restrict str)
{
    return Strtol(str, 10);
}
