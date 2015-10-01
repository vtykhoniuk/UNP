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

#include <errno.h>


#define CHELPER_MAXLINE	1024

/* Fatal error related to system call
   Print and terminate */
void err_sys(const char* fmt, ...);

/* Non fatal error related to system call
   Print error message and return */
void err_ret(const char* fmt, ...);

/* Fatal error unrelated to system call
   Print and terminate */
void err_quit(const char* fmt, ...);

/* Non fatal error unrelated to system call
   Print error message and return */
void err_msg(const char* fmt, ...);

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
void Fclose(FILE*);
void Inet_pton(int af, const char * restrict src, void * restrict dst);
void Connect(int socket, const struct sockaddr *address, socklen_t address_len);
int Select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds, struct timeval *restrict timeout);
long Strtol(const char *restrict str, int base);
long Strtol10(const char *restrict str);

/*
   The function takes null termintated string 'str' and splits it
   in pieces using any of delimiter characters from 'delims'
   The results are put into dst vector. If size of dst vector is
   greater than amount of pieces in str, 'n' is updated
*/
size_t strsplit(char *str, const char *delims, char **dst, size_t n);

#endif // CHELPER_H
