#include "hls.h"

/**
 * openprintclosedir - function that open, print and close directory
 * @path: string that represent the path of the directory
 */

int openprintclosedir(char *path, char *prog_name, int nb, int nb_files, char *options)
{
	struct stat file_stat[1024];
	char *dots[1024] = {NULL};
	char *h_files[1024] = {NULL};
	char *files[1024] = {NULL};
	struct stat dots_stats[1024];
	struct stat h_files_stats[1024];
	struct stat files_stats[1024];
	int dp = 0;
	int hp = 0;
	int p = 0;

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
		int i = 0;

		sprintf(full_path, "%s/%s", path, entry->d_name);

		if (lstat(full_path, &file_stat[i]) == -1)
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
				/*_strcpy(file_stat[i].filename, dots[dp]);*/
				dots_stats[dp] = file_stat[i];
				dp++;
			} else {
				h_files[hp] = entry->d_name;
				/*_strcpy(file_stat[i].filename, h_files[hp]);*/
				h_files_stats[hp] = file_stat[i];
				hp++;
			}
		} else {
			files[p] = entry->d_name;
			/*_strcpy(file_stat[i].filename, files[p]);*/
			files_stats[p] = file_stat[i];
			p++;
		}
		i++;
	}

	/**Print file/directory name*/
	if (is_char_in_str(options, 'a') || is_char_in_str(options, 'A'))
	{
		if (!is_char_in_str(options, 'A'))
		{
			print_files(dp, dots, dots_stats, options);
		}

		print_files(hp, h_files, h_files_stats, options);
	}

	print_files(p, files, files_stats, options);

	if (!is_char_in_str(options, '1') || is_char_in_str(options, 'l'))
	{
		printf("in_open-close_dir\n");
	}

	/**Close the directory*/
	closedir(dir);

	return(0);
}

