#include "hls.h"

/**
 * main- fonction principale
 * no arguments yet
 *
 * Return: 0 if all good 1 if errors
 */


int main(int argc, char *argv[])
{
	int i;
	int realargc = 0;
	char *prog_name = argv[0];

	char *options = getoptions(argc, argv);

	for(i = 1; i < argc; i++)
	{
		if(argv[i][0] != '-')
		{
			realargc++;
		}
	}

	if (realargc == 0)
	{
		openprintclosedir(".", prog_name, realargc, options);
	}
	else
	{	
		for(i = 1; i < argc; i++ )
		{
			lstat(argv[i], &file_stat);

			if (S_ISREG(file_stat.st_mode))
			{
				printf("%s\n", argv[i]);
			}
		}

		if (argc > 1)
		{
			printf("\n");
		}

		for(i = 1; i < argc; i++ )
		{
			lstat(argv[i], &file_stat);

			if(argv[i][0] != '-')
			{
				if (S_ISDIR(file_stat.st_mode))
				{
					openprintclosedir(argv[i], prog_name, realargc, options);
				} else {
					fprintf(stderr, "%s: cannot access %s: ", prog_name, argv[i]);
					perror("");
					return(1);
				}

			}
		}
	}

	free(options);
	return (0);
}
