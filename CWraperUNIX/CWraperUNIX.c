#include "CWraperUNIX.h"
#include "CError.h"

#include <unistd.h>


void Close(int fd)
{
    if (close(fd) != 0)
        err_sys("Error closing file descriptor");
}
