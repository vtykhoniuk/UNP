#include "CArray.h"
#include "CHelper.h"

#include <assert.h>
#include <string.h>

#define WHITE       " \t\n"

int **read_matrix(size_t rows, size_t cols, FILE * stream, char *buf, size_t buf_size)
{
    int **a;
    int i, j;
    CLinkedList *parts;
    CLLNode *node;

    assert(rows > 0);
    assert(cols > 0);

    a = (int**) malloc(rows*sizeof(int*));

    for (i = 0; i < rows; ++i) {
        a[i] = (int*) malloc(cols*sizeof(int));

        Fgets(buf, buf_size, stream);
        parts = strsplit(buf, WHITE);

        if (parts->size != cols) {
            CLL_destroy(parts, destroy_char_value);
            err_quit("unable to split line in [%d] parts", cols);
        }

        node = parts->head;

        for (j = 0; j < cols; ++j) {
            a[i][j] = Strtol10(*((char**) node->value));
            node = node->next;
        }

        CLL_destroy(parts, destroy_char_value);
    }

    return a;
}
