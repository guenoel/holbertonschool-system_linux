#include "hls.h"

/**
 * openprintclosedir - function that open, print and close directory
 * @path: string that represent the path of the directory
 */

int openprintclosedir(char *path, char *prog_name, int argc)
{
	dir = opendir(path);
	if (dir == NULL)
	{
		perror(prog_name);
		return (1);
	}
	if (argc > 2)
	{
		printf("%s: ", path);
	}

	if (lstat(path, &file_stat) == 0 && S_ISREG(file_stat.st_mode))
	{	
		printf("%s ", path);
	} else {
		/**Read the directory entries*/
		while ((entry = readdir(dir)) != NULL)
		{
			char full_path[1024];
			sprintf(full_path, "%s/%s", path, entry->d_name);

			if (lstat(full_path, &file_stat) == -1)
			{
				perror(prog_name);
				closedir(dir);
				return (1);
			}

			/**Print file/directory name*/
			if (entry->d_name[0] != '.')
			{
				printf("%s ", entry->d_name);
			}
		}

		/**Close the directory*/
		closedir(dir);
	}
	return(0);
}

