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
	int file_c = 0;

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
		file_c = print_files(argc, argv, options);
		print_folders(argc, realargc, argv, options, file_c);
	}
	free(options);
	return (0);
}
