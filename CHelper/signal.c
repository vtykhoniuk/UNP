#include "CHelper.h"

Sigfunc* signal(int signo, Sigfunc* func)
{
    struct sigaction act, oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    /* Restart blocked services unless this is SIGALARM handler
       Since SIGALRM is used to set timers for I/O syscalls we do want
       these syscalls to be interrupted when SIGALRM arrived
    */
    if (signo != SIGALRM) {
#ifdef SA_RESTART
        act.sa_flags |= SA_RESTART;
#endif
    }

    if (sigaction(signo, &act, &oact) < 0)
        return SIG_ERR;

    return oact.sa_handler;
}
