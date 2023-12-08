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

	/* Disable buffering on stdout */
	setvbuf(stdout, NULL, _IONBF, 0);

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
		int status;

		waitpid(child_pid, &status, 0);

		/* Trace the child using PTRACE_SINGLESTEP */
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			ptrace(PTRACE_SYSCALL, child_pid, NULL, NULL);
			waitpid(child_pid, &status, 0);
			if (WIFSTOPPED(status))
				print_syscall_num(child_pid);
		}
	}

	return (0);
}

void print_syscall_num(pid_t child_pid)
{
	struct user_regs_struct regs;

	if (ptrace(PTRACE_GETREGS, child_pid, NULL, &regs) == -1)
	{
		perror("ptrace");
		exit(EXIT_FAILURE);
	}
	printf("%lu\n", (long)regs.orig_rax);
}
