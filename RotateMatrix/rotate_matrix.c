#include <stdlib.h>
#include <string.h>

#include "CArray.h"
#include "CHelper.h"

static void usage();

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
