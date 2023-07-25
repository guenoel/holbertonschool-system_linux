#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/**
 * main- fonction principale
 * no arguments yet
 *
 * Return: 0 if all good 1 if errors
 */


int main(void)
{
	DIR *dir;
	struct dirent *entry;
	struct stat file_stat;

	/**Open the current directory*/
	dir = opendir(".");
	if (dir == NULL)
	{
		perror("Error opening directory");
		return (1);
	}

	/**Read the directory entries*/
	while ((entry = readdir(dir)) != NULL)
	{
		if (lstat(entry->d_name, &file_stat) == -1)
		{
			perror("Error getting file status");
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
	return (0);
}
