#include "laps.h"

/**
 * race_state - function getline
 * @id: pointer to id of car in the array
 * @size: size of array
 */

static car_t *head;

void race_state(int *id, size_t size)
{
    size_t i = 0;
    car_t *current = NULL;

    /*maybe if size equal to 0 we have delete all the list and stop*/
    if (size == 0)
	{
		free_ll();
		return;
	}

    for (i = 0; i < size; i++)
    {
        update_laps(id[i]);
    }

    printf("Race state:");
    /*init current to the start of the list*/
    current = head;
    while(current->next != NULL)
    {
        printf("Car %d [%d laps]", current->id, current->laps);
        current = current->next;
    }

}