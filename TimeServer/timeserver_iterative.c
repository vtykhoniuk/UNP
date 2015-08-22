#include <stdio.h>
#include <stdlib.h>

#include "CNet.h"

#define PORT        1333
#define LINE_MAX    256

int main()
{
    int listenfd, connfd;
    struct sockaddr_in serv_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buff[LINE_MAX+1];
    time_t ticks;

    listenfd = Socket(PF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(listenfd, (SA *) &serv_addr, sizeof(serv_addr));

    Listen(listenfd, 2);

    for (;;) {
        connfd = Accept(listenfd, (SA *) &client_addr, &client_addr_len);

        Snprintf(buff, LINE_MAX, "Connection from [%s]", sock_ntop((SA *) &client_addr, client_addr_len));
        printf("%s\n", buff);

        ticks = time(NULL);
        Snprintf(buff, LINE_MAX, "%s\r\n", ctime(&ticks));

        sock_write(connfd, buff, strlen(buff));

        Close(connfd);
    }

    Close(listenfd);

    exit(EXIT_SUCCESS);
}
