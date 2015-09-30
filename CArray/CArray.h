#ifndef CARRAY_H
#define CARRAY_H

#include <stddef.h>

/* Prints out 'n' elements of size 's' of array 'a',
   using formant 'f' and delimiter 'd'
*/
void print_array(int *a, size_t n);
void print_matrix(int **a, size_t rows, size_t cols);

#endif
