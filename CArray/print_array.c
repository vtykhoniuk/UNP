#include "CArray.h"

#include <stdio.h>

void print_array(int *a, size_t n)
{
    unsigned int i;
    for (i = 0; i < n; ++i)
        printf("%4d", a[i]);

    putchar('\n');
}

void print_matrix(int **a, size_t rows, size_t cols)
{
    unsigned int i, j;
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j)
            printf("%4d", a[i][j]);
        putchar('\n');
    }
}
