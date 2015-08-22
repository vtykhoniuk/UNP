#include "CNet.h"

#include <errno.h>

/*
   read
*/
#include <unistd.h>

size_t sock_read(int sockfd, void *buf, size_t n)
{
    ssize_t readn;
    char *ptr = buf;
    size_t nleft = n;

    while (nleft > 0) {
        if ((readn = read(sockfd, ptr, nleft)) > 0) {
            nleft -= readn;
            ptr += readn;
        } else if (readn == 0)
            break;
        else if (errno != EINTR)
            err_sys("write error");
    }

    return (n - nleft);
}
