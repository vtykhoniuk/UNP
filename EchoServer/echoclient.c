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
    /* CNET_MAXLINE+1: we will output  to the stream whatever we
       read from the socket, using fputs call. We need to reserve
       1 character for '\0'
    */
    char buf[CNET_MAXLINE+1];
    fd_set rset;
    int nfds, streamfd;
    size_t readn;
    int stream_eof = 0;

    streamfd = fileno(stream);

    FD_ZERO(&rset);
    for (;;) {
        FD_SET(sockfd, &rset);
        if (stream_eof == 0)
            FD_SET(streamfd, &rset);

        nfds = MAX(streamfd, sockfd) + 1;

        Select(nfds, &rset, NULL, NULL, NULL);

        if (FD_ISSET(sockfd, &rset)) {
            if ((readn = Read(sockfd, buf, sizeof(buf))) == 0) {
                if (stream_eof)
                    /* This is normal termination condition: we have nothing
                       to send, and server shut down his side of connection
                    */
                    return;
                else
                    /* This is exception: the streamfd is not closed yet which
                       means that we still have data to be sent to the server
                       but server closes the connection probably because of an error
                    */
                    err_quit("str_cli: server terminated prematurely");
            }

            buf[readn] = '\0';
            Fputs(buf, stdout);
        }

        if (FD_ISSET(streamfd, &rset)) {
            if ((readn = Read(streamfd, buf, sizeof buf)) == 0) {
                /* There is nothing else to be sent, whatever we had - we alredy
                   pass to the kernel therefore just half close the connection to
                   the server with shutdown and remove streamfd from the 'select'
                   queue
                */
                stream_eof = 1;
                Shutdown(sockfd, SHUT_WR);
                FD_CLR(streamfd, &rset);
                continue;
            }

            sock_write(sockfd, buf, readn);
        }
    }
}
