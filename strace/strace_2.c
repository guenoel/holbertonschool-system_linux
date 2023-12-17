#include "strace.h"
#include "syscalls.h"

#define ENOSYS_ERROR -38

/**
* createTracedProcess - Crea y configura el proceso hijo para la traza
* @argv: Argument vector
*
* Return: El PID del proceso hijo
*/
pid_t createTracedProcess(char **argv)
{
	pid_t child_pid;

	/* Fork a child to execute the program to be traced */
	child_pid = fork();

	if (child_pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		raise(SIGSTOP);
		execvp(argv[0], argv);
		perror("execvp");
		exit(EXIT_FAILURE);
	}

	return (child_pid);
}

/**
* traceSyscalls - Realiza la traza de las llamadas al sistema
* @child_pid: PID del proceso hijo
*/
void traceSyscalls(pid_t child_pid)
{
	int status, syscall_number, print_syscall_name, call_count = 0;
	struct user_regs_struct user_registers;

	waitpid(child_pid, &status, 0);
	ptrace(PTRACE_SYSCALL, child_pid, 0, 0);

	for (print_syscall_name = 0; !WIFEXITED(status); print_syscall_name ^= 1)
	{
		ptrace(PTRACE_GETREGS, child_pid, 0, &user_registers);

		if (!print_syscall_name && call_count)
		{
			syscall_number = user_registers.orig_rax;
			printf("%s", syscalls_64_g[syscall_number].name);
		}

		if (print_syscall_name && (long)user_registers.rax != ENOSYS_ERROR
									&& call_count)
			printf(" = %s%lx\n", user_registers.rax ? "0x" : "",
					(long)user_registers.rax);

		ptrace(PTRACE_SYSCALL, child_pid, 0, 0);
		waitpid(child_pid, &status, 0);
		call_count = 1;
	}
}

/**
* main - Entry point
* @argc: Argument count
* @argv: Argument vector
*
* Return: EXIT_SUCCESS or EXIT_FAILURE
*/
int main(int argc, char **argv)
{
	pid_t child_pid;

	/* Disable buffering of stdout */
	setvbuf(stdout, NULL, _IONBF, 0);

	/* Check usage */
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	child_pid = createTracedProcess(argv + 1);
	traceSyscalls(child_pid);

	printf(" = ?\n");
	return (EXIT_SUCCESS);
}
