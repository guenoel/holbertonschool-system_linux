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
		memset(&file_stat[i], 0, sizeof(struct stat));
	}
}
