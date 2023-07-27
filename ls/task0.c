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
		if (file_c > 0)
		{
			printf("\n");
		}
		print_folders(argc, realargc, argv, options);
		printf("truc");
	}
	/*if (!is_char_in_str(options, '1'))
	  {
	  printf("\n");
	  }*/

	free(options);
	return (0);
}
