#include "CHelper.h"

#include <string.h>
#include <assert.h>

size_t strsplit(char *str, const char *delims, char **dst, size_t n)
{
    char *token;
    size_t i = 0;

    assert(str != NULL);
    assert(strlen(str) > 0);
    assert(n > 0);

    /* If we got NULL in the first strtok call that probably
       means that 'str' contains nothing but 'delims' characters
       */
    if ((token = strtok(str, delims)) == NULL)
        return 0;

    dst[i++] = token;

    while (i < n && (token = strtok(NULL, delims)) != NULL)
        dst[i++] = token;

    return i;
}
