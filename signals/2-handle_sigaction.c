#include "signals.h"

/**
 * handle_sigaction - catch signal
 * catch signal and execute function with signal number in parameter
 * Return: 0 if ok -1 if error
*/
int handle_sigaction(void)
{
	struct sigaction sigact;

	sigact.sa_handler = sigint_handler;
	sigact.sa_flags = 0;

	if (sigaction(SIGINT, &sigact, NULL) == -1)
		return (-1);
	return (0);
}

/**
 * sigint_handler - print message
 * print a sentence with sig number
 * @signum: number of the signal
*/
void sigint_handler(int signum)
{
	printf("Gotcha! [%d]\n", signum);
	fflush(stdout);
}
