#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

#include "CError.h"
#include "CWraperUNIX.h"

#define PORT    1333
#define LINE_MAX    256

int main()
{
    int listenfd, connfd;
    struct sockaddr_in serv_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buff[LINE_MAX+1], ip[INET_ADDRSTRLEN];
    time_t ticks;

    listenfd = Socket(PF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(listenfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    Listen(listenfd, 2);

    for (;;) {
        connfd = Accept(listenfd, (struct sockaddr *) &client_addr, &client_addr_len);

        if (inet_ntop(AF_INET, &client_addr.sin_addr, ip, client_addr_len) == NULL)
            err_sys("Failed getting client IP");

        if (snprintf(buff, LINE_MAX, "Connection from ip [%s] port [%d]", ip, ntohs(client_addr.sin_port)) < 0)
            err_sys("snprintf error");

        printf("%s\n", buff);

        ticks = time(NULL);
        if (snprintf(buff, LINE_MAX, "%s\r\n", ctime(&ticks)) < 0)
            err_sys("snprintf error");

        Write(connfd, buff, strlen(buff));

        Close(connfd);
    }

    Close(listenfd);

    exit(EXIT_SUCCESS);
}
