#include "CWraperUNIX.h"
#include "CError.h"

#include <stdlib.h>
#include <errno.h>

long Strtol(const char *restrict str, char **restrict endptr, int base)
{
    long r;

    errno = 0;
    r = strtol(str, endptr, base);
    if (errno)
        err_sys("error converting string [%s] to long", str);

    return r;
}

long Strtol10(const char *restrict str)
{
    return Strtol(str, NULL, 10);
}
