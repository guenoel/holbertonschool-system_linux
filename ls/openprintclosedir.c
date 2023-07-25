#include "hls.h"

/**
 * openprintclosedir - function that open, print and close directory
 * @path: string that represent the path of the directory
 */

int openprintclosedir(char *path, char *prog_name)
{
	printf("%s\n", path);
	dir = opendir(path);
        if (dir == NULL)
        {
		fprintf(stderr, "%s: error with opening directory\n", prog_name);
                return (1);
        }

        /**Read the directory entries*/
        while ((entry = readdir(dir)) != NULL)
        {
                if (lstat(entry->d_name, &file_stat) == -1)
                {
			fprintf(stderr, "%s: error getting file status\n", prog_name);
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
	return(0);
}

