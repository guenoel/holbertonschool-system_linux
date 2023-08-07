#ifndef get_line_h
#define get_line_h

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * struct store_line - struct to store each line in a node
 * @size: size of string
 * @line: string of a line
 * @line_finished: bool tell if line is full or not
 * @next: next node of the list
 */

typedef struct store_line
{
	int size;
	char *line;
	bool line_finished;
	struct store_line *next;
} store_t;

store_t *new_node(unsigned int len);
char *_getline(const int fd);
bool is_char_in_str(const char *str, char c);
void free_node(store_t *node);
void init_string(char *string, int start, int size);

#define READ_SIZE 1024

#endif
