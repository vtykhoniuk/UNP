#ifndef CNET_H
#define CNET_H

/*
   struct sockaddr
   Address and Protocol families
   Socket related functions
*/
#include <sys/socket.h>


/*
   struct sockaddr_in
*/
#include <netinet/in.h>

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

/*
   err_sys
   err_ret
   err_quit
   err_msg
*/
#include "CError.h"

#include "CWraperUNIX.h"

typedef struct sockaddr SA;

/*
   Returns socket address:
    for IPv4: xxx.xxx.xxx.xxx:port
    for IPv6: NOT IMPLEMENTED
*/
char *sock_ntop(const SA *sa, socklen_t salen);

/*
   Writes 'n' bytes from 'buf' to 'sockfd'
   Handles cases when 'write' syscall returned before 'n' bytes are written
   (because of sys interrupt EINTR or net buffer overflow)
*/
void sock_write(int sockfd, const void *buf, size_t n);
size_t sock_read(int sockfd, void *buf, size_t n);

#define CNET_MAXLINE    1024

size_t sock_readline(int sockfd, void *buf, size_t n);

typedef void Sigfunc(int);
Sigfunc* signal(int signo, Sigfunc* func);
void Signal(int signo, Sigfunc* func);

#define MIN(a,b)        ((a) < (b) ? (a) : (b))
#define MAX(a,b)        ((a) > (b) ? (a) : (b))

#endif // CNET_H
