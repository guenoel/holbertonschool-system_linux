#ifndef SORT_H
#define SORT_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

DIR *dir;
struct dirent *entry;
struct stat file_stat;

int openprintclosedir(char *path, char *prog_name, int argc);

#endif
