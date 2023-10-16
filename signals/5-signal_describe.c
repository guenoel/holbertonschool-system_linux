#include "signals.h"

/**
* main - prints a description of a given signal
*
* @argc: number of arguments
* @argv: array of strings arguments
*
* Return: 1 if OK 0 if failed
*/
int main(int argc, char *argv[])
{
	int signum;

	if (argc != 2)
	{
		printf("Usage: %s <signum>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	signum = atoi(argv[1]);

	if (signum >= 1 && signum <= 64)
	{
		/* const char *signal_name = sys_siglist[signum]; */
		const char *signal_name = strsignal(signum);

		if (signal_name != NULL)
		{
			printf("%d: %s\n", signum, signal_name);
		}
		else
		{
			printf("%d: Unknown signal %d\n", signum, signum);
		}
	}
	else
	{
		printf("%d: Unknown signal %d\n", signum, signum);
	}

	return (EXIT_SUCCESS);
}
