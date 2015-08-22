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

/*
   typedef socklen_t
   inet_ntop
   inet_pton
*/
#include <arpa/inet.h>

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

#endif // CNET_H
