#include "CArray.h"
#include "CHelper.h"

#include <assert.h>
#include <string.h>

#define WHITE       " \t\n"

int **read_matrix(size_t rows, size_t cols, FILE * stream, char *buf, size_t buf_size)
{
    int **a;
    int i, j;
    char *token;

    assert(rows > 0);
    assert(cols > 0);

    a = (int**) malloc(rows*sizeof(int*));

    for (i = 0; i < rows; ++i) {
        a[i] = (int*) malloc(cols*sizeof(int));

        Fgets(buf, buf_size, stream);

        if ((token = strtok(buf, WHITE)) == NULL)
            err_quit("invalid input in line [%d]", i);

        a[i][0] = Strtol10(token);

        for (j = 1; j < cols && (token = strtok(NULL, WHITE)) != NULL; ++j)
            a[i][j] = Strtol10(token);

        if (j < cols)
            err_quit("invalid input in line [%d]", i);
    }

    return a;
}
