#include "CWraperUNIX.h"
#include "CError.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdarg.h>
#include <stdio.h>


void Close(int fd)
{
    if (close(fd) == -1)
        err_sys("close error");
}

pid_t Fork()
{
    pid_t pid;

    if ((pid = fork()) == -1)
        err_sys("fork error");

    return pid;
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

void Write(int fd, const void *buf, size_t count)
{
    if (write(fd, buf, count) != count)
        err_sys("write error");
}

void Snprintf(char * restrict str, size_t size, const char * restrict format, ...)
{
    va_list ap;

    va_start(ap, format);

    if (vsnprintf(str, size, format, ap) < 0)
        err_sys("vsnprintf error");

    va_end(ap);
}
