#include "CArray.h"

#include <stdlib.h>

void free_matrix(int **a, size_t rows)
{
    int i;

    for (i = 0; i < rows; ++i)
        free(a[i]);

    free(a);
}
