#include "signals.h"

/**
 * current_handler_sigaction - Gets and returns the current signal handler
* for the SIGINT signal.
*
* Return: pointer of function that manage SIGINT.
* If the current handle cannot be obtained or if it is an error, NULL is
* returned.
*/
void (*current_handler_sigaction(void))(int)
{
	struct sigaction sigact;

	if (sigaction(SIGINT, NULL, &sigact) == -1)
		return (NULL);
	return (sigact.sa_handler);
}
