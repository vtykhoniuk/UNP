#ifndef CHELPER_H
#define CHELPER_H

#include <stdlib.h>

/*
   typedef FILE
*/
#include <stdio.h>

/*
   typedef timeval
*/
#include <sys/time.h>
#include <time.h>

/*
   typedef size_t
*/
#include <sys/types.h>

/*
   typedef socklen_t
   struct sockaddr
*/
#include <arpa/inet.h>

/*
   Error processing is used in almost all functions
*/
#include "CError.h"

void Close(int);
void Shutdown(int socket, int how);
pid_t Fork(void);
int Socket(int domain, int type, int protocol);
void Bind(int sockfd, struct sockaddr *my_addr, socklen_t addrlen);
void Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
size_t Write(int fd, const void *buf, size_t count);
size_t Read(int fildes, void *buf, size_t nbyte);
void Snprintf(char * restrict str, size_t size, const char * restrict format, ...);
void Fputs(const char *restrict s, FILE *restrict stream);
char* Fgets(char * restrict str, int size, FILE * restrict stream);
void Inet_pton(int af, const char * restrict src, void * restrict dst);
void Connect(int socket, const struct sockaddr *address, socklen_t address_len);
int Select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds, struct timeval *restrict timeout);
long Strtol(const char *restrict str, int base);
long Strtol10(const char *restrict str);

#endif // CHELPER_H
