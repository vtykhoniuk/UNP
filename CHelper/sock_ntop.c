#include "CHelper.h"

char *sock_ntop(const SA *sa, socklen_t salen)
{
    static char str[128];
    char portstr[8];

    switch (sa->sa_family) {
        case AF_INET: {
            const struct sockaddr_in *sin = (const struct sockaddr_in *) sa;

            /* Consider inet_ntop error as non-fatal */
            if (inet_ntop(AF_INET, &sin->sin_addr, str, salen) == NULL)
                err_ret("inet_ntop error");
            else if (sin->sin_port == 0)
                err_msg("inet_ntop returned sin->sin_port == 0");
            else {
                Snprintf(portstr, sizeof(portstr), ":%d", ntohs(sin->sin_port));
                strcat(str, portstr);
            }

            return str;
        }

        default: {
            Snprintf(str, sizeof(str), "sock_ntop: unknown AF_xxx: %d, len %d", sa->sa_family, salen);
            return str;
        }
    }
}
