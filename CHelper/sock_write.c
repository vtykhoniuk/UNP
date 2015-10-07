#include "CHelper.h"


void sock_write(int sockfd, const void *buf, size_t n)
{
    ssize_t written;
    const char *ptr = buf;
    size_t nleft = n;

    while (nleft > 0) {
        if ((written = write(sockfd, ptr, nleft)) >= 0) {
            nleft -= written;
            ptr += written;
        } else if (errno != EINTR)
            err_sys("write error");
    }
}
