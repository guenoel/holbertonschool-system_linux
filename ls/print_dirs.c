#include "hls.h"

int print_dirs(int nb, char *dirs[], char *options, char *prog_name)
{
	int i;

	for(i = 0; i < nb; i++)
	{
		if (i > 0)
		{
			printf("\n");
		} else {
			/*if (nb != 2)
			{
				printf("num2\n");
			}*/
		}
		openprintclosedir(dirs[i], prog_name, nb, options);
	}
	return(0);
}

