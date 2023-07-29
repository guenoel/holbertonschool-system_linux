#include "hls.h"

/**
 * print_files - print all files of arguments
 * @argc: numer of arguments
 * @argv: array of arguments
 * @options: string with all option characters
 *
 * return number of files printed
 */

void print_files(int nb_files, int nb_dirs, char *files[], char *options)
{
	int i;

	for(i = 0; i < nb_files; i++ )
	{
		printf("%s", files[i]);
		if(is_char_in_str(options, '1'))
		{
			printf("\n");
		} else {
			printf(" ");
		}
	}
	if (nb_dirs > 0)
	{
		if(!is_char_in_str(options, '1') && !is_char_in_str(options, 'a'))
		{
			printf("\n");
		}
		if (nb_files > 0 && is_char_in_str(options, 'a') && (!is_char_in_str(options, '1')))
		{
			printf("\n");
		}
		if (nb_files > 0)
		{
			printf("\n");
		}
	}
}
