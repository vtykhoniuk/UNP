#include "CNet.h"

#define PORT            30000
#define ADDR            "127.0.0.1"

void str_cli(FILE*, int);

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof servaddr);
    servaddr.sin_family = AF_INET;
    Inet_pton(AF_INET, ADDR, (SA *) &servaddr.sin_addr.s_addr);
    servaddr.sin_port = htons(PORT);

    sockfd = Socket(PF_INET, SOCK_STREAM, 0);
    Connect(sockfd, (SA *) &servaddr, sizeof servaddr);

    str_cli(stdin, sockfd);

    Close(sockfd);

    exit(EXIT_SUCCESS);
}

void str_cli(FILE* f, int sockfd)
{
    char buf[CNET_MAXLINE];

    while (Fgets(buf, sizeof buf, f) != NULL) {
        sock_write(sockfd, buf, strlen(buf));

        while (sock_readline(sockfd, buf, sizeof buf) == 0)
            err_quit("str_cli: server terminated prematurely");

        Fputs(buf, stdout);
    }
}
