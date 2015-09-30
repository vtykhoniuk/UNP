#include <stdlib.h>
#include <string.h>

#include "CError.h"
#include "CArray.h"
#include "CWraperUNIX.h"

#define BUFFER_MAX  1024
#define WHITE       " \t\n"

static void usage();

int main(int argc, char** argv)
{
    FILE *f;
    char buf[BUFFER_MAX];
    unsigned int rows, cols, i, j;
    int **a;
    char *token;

    if (argc != 2) {
        usage();
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-") == 0)
        f = stdin;
    else if ((f = fopen(argv[1], "r")) == NULL)
        err_sys("Failed to open file [%s]", argv[1]);

    Getline(buf, BUFFER_MAX, f);
    buf[strlen(buf)-1] = '\0';
    rows = Strtol10(buf);

    a = (int**) malloc(rows*sizeof(int*));

    Getline(buf, BUFFER_MAX, f);
    buf[strlen(buf)-1] = '\0';
    cols = Strtol10(buf);

    if (cols == 0)
        err_quit("invalid number of columns: %d", cols);

    for (i = 0; i < rows; ++i) {
        a[i] = (int*) malloc(cols*sizeof(int));

        Getline(buf, BUFFER_MAX, f);

        if ((token = strtok(buf, WHITE)) == NULL)
            err_quit("invalid input in line [%d]", i);

        a[i][0] = Strtol10(token);

        for (j = 1; j < cols && (token = strtok(NULL, WHITE)) != NULL; ++j)
            a[i][j] = Strtol10(token);

        if (j < cols)
            err_quit("invalid input in line [%d]", i);
    }

    print_matrix(a, rows, cols);

    if (ferror(f))
        err_sys("input error");

    if (f != stdin)
        if (fclose(f) == EOF)
            err_sys("Failed to close file [%s]", argv[1]);

    for (i = 0; i < rows; ++i)
        free(a[i]);

    free(a);

    exit(EXIT_SUCCESS);
}

static void usage()
{
    fprintf(stderr, "USAGE: rotate_matrix [-]|<FILE>\n");
}
