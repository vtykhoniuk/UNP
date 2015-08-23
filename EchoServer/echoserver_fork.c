#include "CNet.h"

#define PORT            30000
#define LISTEN_QUEUE    10
#define LOGLINE_MAX     1024

void str_echo(int);
void sig_chld(int);

int main()
{
    int listenfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len = sizeof cliaddr;
    char log[LOGLINE_MAX+1];

    bzero(&servaddr, sizeof servaddr);
    bzero(&cliaddr, cliaddr_len);

    Signal(SIGCHLD, sig_chld);

    listenfd = Socket(PF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    Bind(listenfd, (SA *) &servaddr, sizeof servaddr);
    Listen(listenfd, LISTEN_QUEUE);

    for (;;) {
        connfd = Accept(listenfd, (SA *) &cliaddr, &cliaddr_len);
        Snprintf(log, LOGLINE_MAX, "Connection from [%s]", sock_ntop((SA *) &cliaddr, cliaddr_len));
        fprintf(stderr, "%s\n", log);

        if (Fork() == 0) {
            Close(listenfd);
            str_echo(connfd);
            exit(EXIT_SUCCESS);
        }

        Close(connfd);
    }

    Close(listenfd);

    exit(EXIT_SUCCESS);
}

void str_echo(int sockfd)
{
    int readn;
    char buf[CNET_MAXLINE];

    again:
    while ((readn = read(sockfd, buf, sizeof buf)) > 0)
        sock_write(sockfd, buf, readn);

    if (readn < 0 && errno == EINTR)
        goto again;
    else if (readn < 0)
        err_sys("read error");
}

void sig_chld(int signo)
{
    pid_t chld_pid;
    int chld_status;
    char buf[CNET_MAXLINE];

    while ((chld_pid = waitpid(-1, &chld_status, WNOHANG)) > 0) {
        Snprintf(buf, sizeof buf, "Utilizing child [%ld], status [%d]\n", chld_pid, chld_status);
        Fputs(buf, stderr);
    }

    /* Not really necessary, though this is a way to show that
       system calls that were run when the handler has been invoced MIGHT
       exit with errno == EINTR. This is a good style to make sure your code
       handles such cases gracefuly (UNP p.134)
    */
    return;
}
