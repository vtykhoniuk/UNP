#ifndef CWRAPERUNIX_H
#define CWRAPERUNIX_H

#include <arpa/inet.h>
#include <sys/types.h>

void Close(int);

pid_t Fork(void);

int Socket(int domain, int type, int protocol);

void Bind(int sockfd, struct sockaddr *my_addr, socklen_t addrlen);

void Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

void Write(int fd, const void *buf, size_t count);

#endif // CWRAPERUNIX_H
