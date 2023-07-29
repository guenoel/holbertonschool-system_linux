#include "hls.h"

/**
 * print_details - print details of a file
 * @file: file name to print details from
 *
 * return nothing
 */

void print_details(struct stat stats)
{
	char *formatted_date = format_date(ctime(&stats.st_mtime));

	/*-4lu for links ?*/
	printf("%s %lu %d %d %4ld %s ", permissions_string(stats.st_mode), stats.st_nlink, stats.st_uid, stats.st_gid, stats.st_size, formatted_date);

	free(formatted_date);
}
