#ifndef get_line_h
#define get_line_h

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
char *_getline(const int fd);

#define READ_SIZE 1024

#endif