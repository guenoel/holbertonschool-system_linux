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
	char *files[1024];
	char *dirs[1024];
	int nb_files = 0;
	int nb_dirs = 0;

	char *options = getoptions(argc, argv);

	for(i = 1; i < argc; i++)
	{
		lstat(argv[i], &file_stat);

		if(argv[i][0] != '-')
		{
			if (S_ISREG(file_stat.st_mode))
			{
				files[nb_files] = argv[i];
				nb_files++;
			}
			if (S_ISDIR(file_stat.st_mode))
			{
				dirs[nb_dirs] = argv[i];
				nb_dirs++;
			}
			realargc++;
		}
	}

	if (realargc == 0)
	{
		openprintclosedir(".", prog_name, realargc, options);
	}
	else
	{
		print_files(nb_files, nb_dirs, files, options);
		print_dirs(nb_dirs, dirs, options, prog_name);
	}
	free(options);
	return (0);
}
