#include "hls.h"

/**
 * openprintclosedir - function that open, print and close directory
 * @path: string that represent the path of the directory
 */

int openprintclosedir(char *path, char *prog_name, int nb, int nb_files, char *options)
{

	char *h_files[1024];
	char *files[1024];
	int hp;
	int p;

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

		/*TODO verifier l incrementation de la linked list et le storage en array respectif*/
		if (entry->d_name[0] == '.')
		{
			h_files[hp] = entry->d_name;
			hp++;
		} else {
			files[p] = entry->d_name;
			p++;
		}
	}

	/**Print file/directory name*/
	if (is_char_in_str(options, 'h'))
	{
		int i = 0;

		for(i = 0; i < hp; i++)
		{
			printf("ih: %d\n", i);
			printf("%s", h_files[i]);
			if (is_char_in_str(options, '1'))
			{
				printf("\n");
			} else {
				printf(" ");
			}
		}
	}

	int j = 0;

	for(j = 0; j < p; j++)
	{
		printf("j: %d\n", j);
		printf("%s", files[j]);
		if (is_char_in_str(options, '1'))
		{
			printf("\n");
		} else {
			printf(" ");
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

