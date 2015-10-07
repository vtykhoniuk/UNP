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

#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include "CHelper.h"

/*
   Writes 'n' bytes from 'buf' to 'sockfd'
   Handles cases when 'write' syscall returned before 'n' bytes are written
   (because of sys interrupt EINTR or net buffer overflow)
*/
void sock_write(int sockfd, const void *buf, size_t n);
size_t sock_read(int sockfd, void *buf, size_t n);

size_t sock_readline(int sockfd, void *buf, size_t n);


#endif // CNET_H
