#include "hls.h"

void print_files(int argc, char *argv[], char *options)
{
	int i;

	for(i = 1; i < argc; i++ )
	{   
		lstat(argv[i], &file_stat);

		if (S_ISREG(file_stat.st_mode))
		{   
			printf("%s", argv[i]);
			if(is_char_in_str(options, '1'))
			{
				printf("\n");
			} else {
				printf(" ");
			}
		}   
	}
       printf("\n");	
}
