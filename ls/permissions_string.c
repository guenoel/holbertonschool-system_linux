#include "hls.h"

/**
 * permissions_string - create a string with permissions of a file
 * @mode: statistics of entry
 *
 * Return: string with permissions
 */

const char *permissions_string(mode_t mode) {
	static char perm_str[10];
	/* File type */
	perm_str[0] = (S_ISDIR(mode)) ? 'd' : '-';
	/* Owner permissions */
	perm_str[1] = (mode & S_IRUSR) ? 'r' : '-';
	perm_str[2] = (mode & S_IWUSR) ? 'w' : '-';
	perm_str[3] = (mode & S_IXUSR) ? 'x' : '-';
	/* Group permissions */
	perm_str[4] = (mode & S_IRGRP) ? 'r' : '-';
	perm_str[5] = (mode & S_IWGRP) ? 'w' : '-';
	perm_str[6] = (mode & S_IXGRP) ? 'x' : '-';
	/* Other permissions */
	perm_str[7] = (mode & S_IROTH) ? 'r' : '-';
	perm_str[8] = (mode & S_IWOTH) ? 'w' : '-';
	perm_str[9] = (mode & S_IXOTH) ? 'x' : '-';
	perm_str[10] = '\0';

	return perm_str;
}
