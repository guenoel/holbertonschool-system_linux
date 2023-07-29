#include "hls.h"

int print_dirs(int nb, int nb_files, char *dirs[], char *options, char *prog_name)
{
	int i;

	for(i = 0; i < nb; i++)
	{
		if (i > 0)
		{
			printf("in_print_dirs function@\n");
		}
		openprintclosedir(dirs[i], prog_name, nb, nb_files, options);
	}
	return(0);
}

