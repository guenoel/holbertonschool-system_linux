#include "signals.h"

/**
* current_handler_signal - Gets and returns the current signal handler
* for the SIGINT signal.
*
* Return: pointer of function that manage SIGINT.
* If the current handle cannot be obtained or if it is an error, NULL is
* returned.
*/
void (*current_handler_signal(void))(int)
{
/* Gets the current handler for SIGINT and stores it in 'handler'.*/
	void (*handler)(int) = signal(SIGINT, SIG_DFL);

/* Restores the original SIGIN handler*/
	signal(SIGINT, handler);

/* Returns the current handler or NULL if an error occurred.*/
	return ((handler == SIG_ERR) ? NULL : handler);
}
