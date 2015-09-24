#include "CNet.h"

#define LISTEN_QUEUE    10

static void usage();
void str_echo(int);
void sig_chld(int);

int main(int argc, char **argv)
{
    int listenfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len = sizeof cliaddr;
    char log[CERROR_MAXLINE];
    char c;

    opterr = 0;
    while ((c = getopt(argc, argv, "h")) != EOF) {
        switch (c) {
            case 'h':
                usage();
                exit(EXIT_SUCCESS);
                break;

            case '?':
                usage();
                err_quit("unrecognized option");
        }
    }

    if (argc != 2)
        err_quit("missing <port>");

    bzero(&servaddr, sizeof servaddr);
    bzero(&cliaddr, cliaddr_len);

    Signal(SIGCHLD, sig_chld);

    listenfd = Socket(PF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(Strtol10(argv[1]));

    Bind(listenfd, (SA *) &servaddr, sizeof servaddr);
    Listen(listenfd, LISTEN_QUEUE);

    for (;;) {
        connfd = Accept(listenfd, (SA *) &cliaddr, &cliaddr_len);
        Snprintf(log, sizeof log, "Connection from [%s]", sock_ntop((SA *) &cliaddr, cliaddr_len));
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

    /* Let's use 'read' here (not Read wraper) because I want to process
       EINTR error if it happens.
    */
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
    char log[CERROR_MAXLINE];

    while ((chld_pid = waitpid(-1, &chld_status, WNOHANG)) > 0) {
        Snprintf(log, sizeof log, "Utilizing child [%ld], status [%d]\n", chld_pid, chld_status);
        Fputs(log, stderr);
    }

    /* Not really necessary, though this is a way to show that
       system calls that were run when the handler has been invoced MIGHT
       exit with errno == EINTR. This is a good style to make sure your code
       handles such cases gracefuly (UNP p.134)
    */
    return;
}

static void usage()
{
    err_msg(
"Usage: echoserver [ options ] <port>\n"
"options: -h    print this message"
);
}
