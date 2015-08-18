#include "CNet.h"
#include "CError.h"

#include <unistd.h>

int Close(int fd)
{
    if (close(fd) != 0)
        err_sys("Failed closing socket");

    return 0;
}
