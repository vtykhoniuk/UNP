#include <stdlib.h>
#include <string.h>

#include "CError.h"
#include "CArray.h"
#include "CWraperUNIX.h"

#define BUFFER_MAX  1024

static void usage();

int main(int argc, char** argv)
{
    FILE *stream;
    char buf[BUFFER_MAX];
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

    Getline(buf, BUFFER_MAX, stream);
    buf[strlen(buf)-1] = '\0';
    n = Strtol10(buf);
    
    if (n == 0)
        err_quit("invalid matrix size: [%d]", n);

    a = read_matrix(n, n, stream, buf, BUFFER_MAX);

    if (stream != stdin)
        if (fclose(stream) == EOF)
            err_sys("Failed to close file [%s]", argv[1]);

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
