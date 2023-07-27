#include "hls.h"

/**
 * getoptions - function that store option letters
 * @argv: all arguments
 *
 * Return: string with all option letters
 */

char *getoptions(int argc, char *argv[])
{
	int i;
	char *options = (char *)malloc(1024);

	if (options == NULL) {
		fprintf(stderr, "Memory allocation error\n");
		exit(1);
	}

	options[0] = '\0';

	for(i = 1; i < argc; i++)
	{
		if(argv[i][0] == '-')
		{
			char *opt = argv[i] + 1;
			char *opts = options;
			_strcat(opts, opt);
		}
	}

	return (options);
}

