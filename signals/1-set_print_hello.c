#include "signals.h"

/**
* print_hello - print message
*
* @signum: signal number received
* Return: void
*/
void print_hello(int signum)
{
	(void)signum;
	printf("Hello :)\n");
	fflush(stdout);
}

/**
* set_print_hello - Manage print for SIGINT (Ctrl+C)
* to print "Hello :)"
* Return: void
*/
void set_print_hello(void)
{
	signal(SIGINT, print_hello);
}