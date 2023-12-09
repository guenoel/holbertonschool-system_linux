#include "strace.h"

/**
 * main - Entry point
 *
 * @argc: The number of arguments
 * @argv: The array of arguments
 *
 * Return: 0 on success, error code otherwise
 */
int main(int argc, char *argv[])
{
	pid_t child_pid;
	int status, is_last_syscall;
	struct user_regs_struct regs;

	if (argc < 2)
	{
		/* No command-line arguments */
		fprintf(stderr, "Usage: %s <command>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	/* Create a new child process */
	child_pid = fork();

	/* Check if fork() was successful */
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	/* Check if we're the child process */
	if (child_pid == 0)
	{
		/* Child process */
		if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1)
		{
			perror("ptrace");
			exit(EXIT_FAILURE);
		}

		/* Execute the command */
		execvp(argv[1], &argv[1]);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		wait(&status);
		/* Wait for the child to stop on its first instruction */
		ptrace(PTRACE_SYSCALL, child_pid, 0, 0);
		/* Main tracing loop */
		for (is_last_syscall = 0; !WIFEXITED(status); is_last_syscall ^= 1)
		{
			wait(&status);
			/* Get the registers of the child process */
			ptrace(PTRACE_GETREGS, child_pid, 0, &regs);
			/* Print the system call number every other time */
			if (is_last_syscall)
			{
				/* Get the system call number */
				printf("%ld\n", (long)regs.orig_rax);
			}

			/* Continue the execution of the child process */
			ptrace(PTRACE_SYSCALL, child_pid, 0, 0);
		}
	}
	return (0);
}
