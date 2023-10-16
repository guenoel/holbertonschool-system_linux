#include "signals.h"

/**
* sigquit_handler - Signal handler for SIGQUIT.
*
* @signum: The received signal number (must be SIGQUIT).
*/
void sigquit_handler(int signum)
{
	pid_t sender_pid = 0;

	if (signum == SIGQUIT)
	{
		printf("SIGQUIT sent by %i\n", sender_pid);
	}
}

/**
* trace_signal_sender - Configures a signal handler for SIGQUIT that prints
* the sender's PID when SIGQUIT is received.
*
* Return: 0 if the signal handler configuration was successful, -1 on failure.
*/
int trace_signal_sender(void)
{
	struct sigaction sigact;

	sigact.sa_handler = sigquit_handler;
	sigact.sa_flags = SA_SIGINFO;

	if (sigaction(SIGQUIT, &sigact, NULL) == -1)
		return (-1);
	return (0);
}
