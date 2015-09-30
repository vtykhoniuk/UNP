#include "CArray.h"

#include <stdlib.h>

void free_matrix(int **a, size_t n)
{
    int i;

    for (i = 0; i < n; ++i)
        free(a[i]);

    free(a);
}
