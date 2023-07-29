#include "hls.h"

/**
 * init_struct_stat - initialise à 0 une struct stat
 * @file_stat: l'adresse de la struct a initialiser
 *
 */

void init_struct_stat(struct stat file_stat[1024])
{
	int i = 0;

	for (i = 0; i < 1024; i++) {
		file_stat[i].st_dev = 0;
		file_stat[i].st_ino = 0;
		file_stat[i].st_mode = 0;
		file_stat[i].st_nlink = 0;
		file_stat[i].st_uid = 0;
		file_stat[i].st_gid = 0;
		file_stat[i].st_rdev = 0;
		file_stat[i].st_size = 0;
		file_stat[i].st_blksize = 0;
		file_stat[i].st_blocks = 0;
		file_stat[i].st_atime = 0;
		file_stat[i].st_mtime = 0;
		file_stat[i].st_ctime = 0;
	}
}
