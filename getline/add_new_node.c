#include "laps.h"

void add_new_node(int id)
{
    /*create and fill new node (except next var)*/
    car_t *new = malloc(sizeof(car_t));
		if (new == NULL)
		{
			fprintf(stderr, "Memory allocation error\n");
			exit(EXIT_FAILURE);
		}
	new->id = id;
	new->laps = 0;

    /*If list haven't any node or id of first node is bigger that the id*/
    if (head == NULL || head->id > id)
	{
        /*it will be NULL if list is empty*/
		new->next = head;
        /*new car is on top of the list*/
		head = new_car;
	}
	else
	{
        /*init current var to start of the list*/
        Car *current = head;
        /*find right position in the list*/
		while (current->next != NULL && current->next->id <= id)
		{
			current = current->next;
		}
        /*init next var after new*/
		new->next = current->next;
        /*init next var before new*/
		current->next = new;
    }
}