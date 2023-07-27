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
#include <stdbool.h>

DIR *dir;
struct dirent *entry;
struct stat file_stat;

int openprintclosedir(char *path, char *prog_name, int nb, char *options);
void print_files(int nb_files, int nb_dirs, char *files[], char *options);
int print_dirs(int nb, char *dirs[], char *options, char *prog_name);
char *_strcat(char *dest, char *src);
int _count(char *str);
char *getoptions(int argc, char *argv[]);
bool is_char_in_str(const char *str, char c);

#endif
