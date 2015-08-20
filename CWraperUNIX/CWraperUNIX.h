#ifndef CWRAPERUNIX_H
#define CWRAPERUNIX_H

#include <arpa/inet.h>

void Close(int);

int Socket(int domain, int type, int protocol);

void Bind(int sockfd, struct sockaddr *my_addr, socklen_t addrlen);

void Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

#endif // CWRAPERUNIX_H
