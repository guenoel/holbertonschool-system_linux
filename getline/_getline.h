#ifndef get_line_h
#define get_line_h

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct store_line {
    int size;
    char *line;
    bool line_finished;
    struct store_line *next;
} store_t;

store_t *new_node(unsigned int len);
char *_getline(const int fd);
bool is_char_in_str(const char *str, char c);
void free_node(store_t *node);

#define READ_SIZE 1024

#endif