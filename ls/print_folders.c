#include "hls.h"

int print_folders(int argc, int realargc, char *argv[], char *options)
{
	int i;
	char *prog_name = argv[0];

	for(i = 1; i < argc; ++i)
	{
		lstat(argv[i], &file_stat);

		if(argv[i][0] != '-')
		{
			if (S_ISDIR(file_stat.st_mode))
			{
				if (i > 2)
				{
					printf("\n");
				}
				openprintclosedir(argv[i], prog_name, realargc, options);
			} 
		}
	}

	return(0);
}

