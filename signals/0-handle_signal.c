#include "signals.h"

int handle_signal(void)
{
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
        return (-1);
    return (0);
}

void sigint_handler(int signum)
{
    printf("Gotcha! [%d]\n", signum);
    fflush(stdout);
}