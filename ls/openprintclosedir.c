#include "hls.h"

/**
 * openprintclosedir - function that open, print and close directory
 * @path: string that represent the path of the directory
 */

int openprintclosedir(char *path, char *prog_name, int argc)
{
	lstat(path, &file_stat);

	if (S_ISREG(file_stat.st_mode))
	{	
		printf("%s\n", path);
	} else if (S_ISDIR(file_stat.st_mode)) {
		/**Read the directory entries*/

		dir = opendir(path);
		if (dir == NULL)
		{
			fprintf(stderr, "%s: cannot access %s: ", prog_name, path);
			perror("");
			return (1);
		} else {
			if (argc > 2)
			{
				printf("%s: \n", path);
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
			if (entry->d_name[0] != '.')
			{
				printf("%s ", entry->d_name);
			}
		}

		if (argc > 2)
		{
			printf("\n\n");
		}
		/**Close the directory*/
		closedir(dir);
	} else {
		fprintf(stderr, "%s: cannot access %s: ", prog_name, path);
		perror("");
		return(1);
	}
	return(0);
}

