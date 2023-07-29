#include "hls.h"

/**
 * print_files_in_args - print all files of arguments
 * @nb_files: number of files
 * @files: array of files
 * @options: string with all option characters
 *
 * return nothing
 */

void print_files_in_args(int nb_files, int nb_dirs, char *files[], struct stat file_stats[], char *options)
{
	print_files(nb_files, files, file_stats, options);
	if (nb_dirs > 0)
	{
		if (nb_files > 0)
		{
			if (!is_char_in_str(options, '1'))
			{	
				printf("\n");
			}
			printf("\n");

		}
	}
}
