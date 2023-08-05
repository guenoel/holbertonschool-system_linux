#ifndef get_line_h
#define get_line_h

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct store_line {
    int size;
    char *line;
    struct store_line *next;
} store_t;

store_t *new_node(store_t **head, char *buffer, int len);
char *_getline(const int fd);

#define READ_SIZE 1024

#endif