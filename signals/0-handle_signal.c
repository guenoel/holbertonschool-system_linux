#include "signals.h"

/**
 * handle_signal - catch signal
 * catch signal and execute function with signal number in parameter
 * Return: 0 if ok -1 if error
*/
int handle_signal(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
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
