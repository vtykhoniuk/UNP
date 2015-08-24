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

void str_cli(FILE* stream, int sockfd)
{
    char buf[CNET_MAXLINE];
    struct fd_set rset;
    int nfds, streamfd;
    size_t readn;
    int streameof = 0;

    streamfd = fileno(stream);

    FD_ZERO(&rset);
    for (;;) {
        FD_SET(sockfd, &rset);
        if (streameof == 0)
            FD_SET(streamfd, &rset);

        nfds = MAX(streamfd, sockfd) + 1;

        Select(nfds, &rset, NULL, NULL, NULL);

        if (FD_ISSET(sockfd, &rset)) {
            if ((readn = Read(sockfd, buf, sizeof buf)) == 0) {
                if (streameof)
                    return;
                else
                    err_quit("str_cli: server terminated prematurely");
            }

            sock_write(fileno(stdout), buf, readn);
        }

        if (FD_ISSET(streamfd, &rset)) {
            if ((readn = Read(streamfd, buf, sizeof buf)) == 0) {
                streameof = 1;
                Shutdown(sockfd, SHUT_WR);
                FD_CLR(streamfd, &rset);
                continue;
            }

            Write(sockfd, buf, readn);
        }
    }
}
