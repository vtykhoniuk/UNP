#include "CHelper.h"

/*
   close
   fork
   write
   read
*/
#include <unistd.h>

/*
   va_start
   va_end
*/
#include <stdarg.h>


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

size_t Write(int fd, const void *buf, size_t count)
{
    ssize_t nwritten;

    if ((nwritten = write(fd, buf, count)) == -1)
        err_sys("write error");

    return nwritten;
}

size_t Read(int fildes, void *buf, size_t nbyte)
{
    ssize_t nread;

    if ((nread = read(fildes, buf, nbyte)) == -1)
        err_sys("read error");

    return nread;
}

void Snprintf(char * restrict str, size_t size, const char * restrict format, ...)
{
    va_list ap;

    va_start(ap, format);

    if (vsnprintf(str, size, format, ap) < 0)
        err_sys("vsnprintf error");

    va_end(ap);
}

void Fputs(const char *restrict s, FILE *restrict stream)
{
    if (fputs(s, stream) == EOF)
        err_sys("fputs error");
}

char* Fgets(char * restrict str, int size, FILE * restrict stream)
{
    char *rptr;

    if ((rptr = fgets(str, size, stream)) == NULL && ferror(stream))
        err_sys("fgets error");

    return rptr;
}

void Inet_pton(int af, const char * restrict src, void * restrict dst)
{
    if (inet_pton(af, src, dst) != 1)
        err_sys("inet_pton error");
}

void Connect(int socket, const struct sockaddr *address, socklen_t address_len)
{
    if (connect(socket, address, address_len) != 0)
        err_sys("connect error");
}

int Select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds, struct timeval *restrict timeout)
{
    int n;

    if ((n = select(nfds, readfds, writefds, errorfds, timeout)) == -1)
        err_sys("select error");

    return n;
}

void Shutdown(int socket, int how)
{
    if (shutdown(socket, how) == -1)
        err_sys("shutdown error");
}
