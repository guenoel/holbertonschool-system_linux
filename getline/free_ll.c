#include "laps.h"

/*
 ** free_ll - free nodes of a linked list 
*/

void free_ll(void)
{
	while (head != NULL)
    {	
        /*head variable is always the head until the list doesn't exist anymore*/
		car_t *temp = head;
		head = head->next;
		free(temp);
	}
}