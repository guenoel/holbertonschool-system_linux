#include "signals.h"

/**
* main - send signal to a pid
*
* @argc: number of arguments
* @argv: array of strings arguments
*
* Return: 1 if OK 0 if failed
*/
int main(int argc, char *argv[])
{
	int pid_num;

	if (argc != 2)
	{
		printf("Usage: %s <pid>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	pid_num = atoi(argv[1]);

	if (pid_num == 0)
	{
		printf("Usage: %s <pid>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	if (kill(pid_num, SIGINT) == -1)
	{
		perror("kill");
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
