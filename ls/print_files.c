#include "hls.h"

/**
 * print_files - print all files of arguments
 * @argc: numer of arguments
 * @argv: array of arguments
 * @options: string with all option characters
 *
 * return number of files printed
 */

int print_files(int argc, char *argv[], char *options)
{
	int i;
	int file_c = 0;

	for(i = 1; i < argc; i++ )
	{   
		lstat(argv[i], &file_stat);

		if (S_ISREG(file_stat.st_mode) && argv[i][0] != '-')
		{
			file_c++;
			printf("%s", argv[i]);
			if(is_char_in_str(options, '1'))
			{
				printf("\n");
			} else {
				printf(" ");
			}
		}   
	}
	if (file_c > 0 && !is_char_in_str(options, '1'))
	{
		printf("\n");
	}

	return file_c;
}
