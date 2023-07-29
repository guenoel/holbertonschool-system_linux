#include "hls.h"

/**
 * openprintclosedir - function that open, print and close directory
 * @path: string that represent the path of the directory
 */

int openprintclosedir(char *path, char *prog_name, int nb, int nb_files, char *options)
{

	char *dots[1024] = {NULL};
	char *h_files[1024] = {NULL};
	char *files[1024] = {NULL};
	int dp = 0;
	int hp = 0;
	int p = 0;
	int j = 0;

	/**Read the directory entries*/

	dir = opendir(path);
	if (dir)
	{
		if (nb > 1 || nb_files > 1)
		{
			printf("%s:\n", path);
		}
	} else {	
		if (errno == EACCES)
		{
			fprintf(stderr, "%s: cannot open directory %s: ", prog_name, path);
			perror("");
			return (1);	
		} else {
			fprintf(stderr, "%s: cannot access %s: ", prog_name, path);
			perror("");
			return (1);
		}
	}

	/*store files of directory in two differents arrays: hidden and not hidden*/
	while ((entry = readdir(dir)) != NULL)
	{
		char full_path[1024];

		sprintf(full_path, "%s/%s", path, entry->d_name);

		if (lstat(full_path, &file_stat) == -1)
		{
			fprintf(stderr, "%s: Error getting file status %s: ", prog_name, path);
			perror("");
			closedir(dir);
			return (1);
		}

		if (entry->d_name[0] == '.')
		{
			if (_strcmp(entry->d_name, ".") == 0 || _strcmp(entry->d_name, "..") == 0)
			{
				dots[dp] = entry->d_name;
				dp++;
			} else {
				h_files[hp] = entry->d_name;
				hp++;
			}
		} else {
			files[p] = entry->d_name;
			p++;
		}
	}

	/**Print file/directory name*/
	if (is_char_in_str(options, 'a') || is_char_in_str(options, 'A'))
	{
		int i = 0;
		if (!is_char_in_str(options, 'A'))
		{
			for(i = 0; i < dp; i++)
			{
				printf("%s", dots[i]);
				if (is_char_in_str(options, '1'))
				{
					printf("num1\n");
				} else {
					printf(" ");
				}
			}
		}
		for(i = 0; i < hp; i++)
		{
			printf("%s", h_files[i]);
			if (is_char_in_str(options, '1'))
			{
				printf("num2\n");
			} else {
				printf(" ");
			}
		}
	}

	for(j = 0; j < p; j++)
	{
		printf("%s", files[j]);
		if (is_char_in_str(options, '1'))
		{
			printf("num3\n");
		} else {
			printf(" ");
		}
	}
	if(!is_char_in_str(options, '1') || !is_char_in_str(options, 'A'))
	{
		printf("num4\n");
	}

	/**Close the directory*/
	closedir(dir);

	return(0);
}

