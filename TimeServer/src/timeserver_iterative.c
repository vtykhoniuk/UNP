#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>

#include "CError.h"
#include "CNet.h"

#define PORT    1333
#define LINE_MAX    256

int main()
{
    int listenfd, connfd;
    struct sockaddr_in serv_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buf[LINE_MAX+1], ip[INET_ADDRSTRLEN];

    listenfd = socket(PF_INET, SOCK_STREAM, 0);
    if (listenfd == -1)
        err_sys("Failed openning socket");

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) != 0)
        err_sys("Failed bind socket");

    if (listen(listenfd, 2) != 0)
        err_sys("Failed listen on socket");

    for (;;) {
        if ((connfd = accept(listenfd, (struct sockaddr *) &client_addr, &client_addr_len)) == -1)
            err_sys("Failed accept connection");

        if (inet_ntop(AF_INET, &client_addr.sin_addr, ip, client_addr_len) == NULL)
            err_sys("Failed getting client IP");

        snprintf(buf, LINE_MAX, "Connection from ip [%s] port [%d]\n", ip, ntohs(client_addr.sin_port));
        printf("%s", buf);

        Close(connfd);
    }

    Close(listenfd);

    exit(EXIT_SUCCESS);
}
