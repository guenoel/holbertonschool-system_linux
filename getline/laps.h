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

/*define struct and typedef car_t*/
typedef struct car
{
int id;
int laps;
struct car *next;
} car_t;

void race_state(int *id, size_t size);
void update_laps(int id);
void add_new_node(int id);
void free_ll(void);

#endif
