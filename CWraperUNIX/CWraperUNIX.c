#include "CWraperUNIX.h"
#include "CError.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>


void Close(int fd)
{
    if (close(fd) == -1)
        err_sys("close error");
}

int Socket(int domain, int type, int protocol)
{
    int fd;

    if ((fd = socket(domain, type, protocol)) < 0)
        err_sys("socket error");

    return fd;
}

void Bind(int sockfd, struct sockaddr *my_addr, socklen_t addrlen)
{
    if (bind(sockfd, my_addr, addrlen) != 0)
        err_sys("bind error");
}

void Listen(int sockfd, int backlog)
{
    if (listen(sockfd, backlog) < 0)
        err_sys("listen error");
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int fd;

    if ((fd = accept(sockfd, addr, addrlen)) == -1)
        err_sys("accept error");

    return fd;
}
