#include "CWraperUNIX.h"
#include "CError.h"

char* Getline(char * restrict str, int size, FILE * restrict stream)
{
    if (fgets(str, size, stream) == NULL)
        if (ferror(stream))
            err_sys("input error");

    return str;
}
