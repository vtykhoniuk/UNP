#ifndef CARRAY_H
#define CARRAY_H

#include <stddef.h>
#include <stdio.h>

/* Prints out 'n' elements of size 's' of array 'a',
   using formant 'f' and delimiter 'd'
*/
void print_array(int *a, size_t n);
void print_matrix(int **a, size_t rows, size_t cols);

int **read_matrix(size_t rows, size_t cols, FILE * stream, char *buf, size_t buf_size);
void free_matrix(int **a, size_t rows);

#endif
