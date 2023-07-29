#include "hls.h"

/**
 * print_files - print all files of an array
 * @nb_files: number of files
 * @files: array of files
 * @options: string with all option characters
 *
 * return nothing
 */

void print_files(int nb_files, char *files[], struct stat file_stats[], char *options)
{
	int i;

	for(i = 0; i < nb_files; i++ )
	{
		if (is_char_in_str(options, 'l'))
		{
			print_details(file_stats[i]);
		}
		printf("%s", files[i]);
		if(is_char_in_str(options, '1') || is_char_in_str(options, 'l'))
		{
			printf("in_print_files\n");
		} else {
			printf(" ");
		}
	}
}
