#include "CArray.h"
#include "CHelper.h"

#include <assert.h>
#include <string.h>

#define WHITE       " \t\n"

int **read_matrix(size_t rows, size_t cols, FILE * stream, char *buf, size_t buf_size)
{
    int **a;
    int i, j;
    char **parts;

    assert(rows > 0);
    assert(cols > 0);

    a = (int**) malloc(rows*sizeof(int*));

    for (i = 0; i < rows; ++i) {
        a[i] = (int*) malloc(cols*sizeof(int));
        parts = (char**) malloc(cols*sizeof(char*));

        Fgets(buf, buf_size, stream);
        if (strsplit(buf, WHITE, parts, cols) != cols) {
            err_quit("unable to split line in [%d] parts", cols);
            free(parts);
        }

        for (j = 0; j < cols; ++j)
            a[i][j] = Strtol10(parts[j]);
    }

    return a;
}
