#include "CNet.h"


size_t sock_readline(int sockfd, void *buf, size_t n)
{
    char *ptr = buf;
    char c;
    int i, readn;

    for (i = 1; i <= n; ++i) {
again:
        if ((readn = read(sockfd, &c, 1)) == 1) {
            *ptr++ = c;
            if (c == '\n')
                break;
        } else if (readn == 0) {
            *ptr = '\0';
            return (i - 1);
        } else if (errno == EINTR)
            goto again;
        else
            err_sys("read error");
    }

    *ptr = '\0';

    return i;
}
