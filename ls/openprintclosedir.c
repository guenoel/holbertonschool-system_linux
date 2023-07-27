#include "hls.h"

/**
 * openprintclosedir - function that open, print and close directory
 * @path: string that represent the path of the directory
 */

int openprintclosedir(char *path, char *prog_name, int nb, int nb_files, char *options)
{
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

		/**Print file/directory name*/
		if (entry->d_name[0] != '.' && !is_char_in_str(options, 'h'))
		{
			printf("%s", entry->d_name);
			if (is_char_in_str(options, '1'))
			{
				printf("\n");
			} else {
				printf(" ");
			}
		}
	}
	if (!is_char_in_str(options, '1'))
	{
		printf("\n");
	}

	/**Close the directory*/
	closedir(dir);

	return(0);
}

