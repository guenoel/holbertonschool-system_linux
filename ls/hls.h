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

int openprintclosedir(char *path, char *prog_name, int nb, int nb_files, char *options);
void print_files_in_args(int nb_files, int nb_dirs, char *files[], struct stat file_stats[], char *options);
void print_files(int nb_files, char *files[], struct stat file_stats[], char *options);
void print_details(struct stat stats);
int print_dirs(int nb, int nb_files, char *dirs[], char *options, char *prog_name);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _count(char *str);
char *getoptions(int argc, char *argv[]);
bool is_char_in_str(const char *str, char c);
const char *permissions_string(mode_t mode);
char *format_date(char * datetime);
void init_struct_stat(struct stat file_stat[1024]);

#endif
