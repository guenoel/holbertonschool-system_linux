#include "hls.h"

/**
 * main - fonction principale
 * no arguments yet
 *
 * Return: 0 if all good 1 if errors
 */


int main(int argc, char *argv[])
{
	int i = 0;
	int realargc = 0;
	char *prog_name = argv[0];
	char *files[1024] = {NULL};
	char *dirs[1024] = {NULL};
	int nb_files = 0;
	int nb_dirs = 0;
	struct stat file_stat[1024];
	struct stat files_stats[1024];
	char *options = getoptions(argc, argv);

	init_struct_stat(file_stat);
	init_struct_stat(files_stats);

	for(i = 1; i < argc; i++)
	{
		lstat(argv[i], &file_stat[i]);

		if(argv[i][0] != '-')
		{
			if (S_ISREG(file_stat[i].st_mode))
			{
				files[nb_files] = argv[i];
				files_stats[nb_files] = file_stat[i];
				nb_files++;
			}
			if (S_ISDIR(file_stat[i].st_mode))
			{
				dirs[nb_dirs] = argv[i];
				nb_dirs++;
			}
			if (!S_ISREG(file_stat[i].st_mode) && (!S_ISDIR(file_stat[i].st_mode)))
			{
				fprintf(stderr, "%s: cannot access %s: ", prog_name, argv[i]);
                        	perror("");
				free(options);
                        	return (1);
			}
			realargc++;
		}
	}

	if (realargc == 0)
	{
		openprintclosedir(".", prog_name, realargc, nb_files, options);
	}
	else
	{
		print_files_in_args(nb_files, nb_dirs, files, files_stats, options);
		print_dirs(nb_dirs, nb_files, dirs, options, prog_name);
	}
	free(options);
	return (0);
}
