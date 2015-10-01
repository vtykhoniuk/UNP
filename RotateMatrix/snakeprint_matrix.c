#include <stdlib.h>
#include <string.h>

#include "CArray.h"
#include "CHelper.h"

static void usage();
void rotate_matrix(int **a, size_t n);
void rotate_matrix_layer(int **a, size_t n, unsigned int i);

int main(int argc, char** argv)
{
    FILE *stream;
    char buf[CHELPER_MAXLINE];
    unsigned int n;
    int **a;

    if (argc != 2) {
        usage();
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-") == 0)
        stream = stdin;
    else if ((stream = fopen(argv[1], "r")) == NULL)
        err_sys("Failed to open file [%s]", argv[1]);

    Fgets(buf, CHELPER_MAXLINE, stream);
    buf[strlen(buf)-1] = '\0';
    n = Strtol10(buf);
    
    if (n == 0)
        err_quit("invalid matrix size: [%d]", n);

    a = read_matrix(n, n, stream, buf, CHELPER_MAXLINE);

    if (stream != stdin)
        Fclose(stream);

    puts("Input matrix:");
    print_matrix(a, n, n);

    rotate_matrix(a, n);
    puts("Rotated matrix:");
    print_matrix(a, n, n);

    free_matrix(a, n);

    exit(EXIT_SUCCESS);
}

static void usage()
{
    fprintf(stderr, "USAGE: rotate_matrix [-]|<FILE>\n");
}

void rotate_matrix(int **a, size_t n)
{
    unsigned int i;

    for (i = 0; i < n/2; ++i)
        rotate_matrix_layer(a, n, i);
}

void rotate_matrix_layer(int **a, size_t n, unsigned int k)
{
    unsigned int lcol = k;
    unsigned int rcol = n - k - 1;
    unsigned int trow = k;
    unsigned int brow = n - k - 1;
    unsigned int i;
    int tmp;

    for (i = 0; i < rcol - lcol; ++i) {
        tmp = a[trow][lcol+i];
        a[trow][lcol+i] = a[brow-i][lcol];
        a[brow-i][lcol] = a[brow][rcol-i];
        a[brow][rcol-i] = a[trow+i][rcol];
        a[trow+i][rcol] = tmp;
    }
}
