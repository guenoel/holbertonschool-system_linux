#include "laps.h"

/**
* update_laps - update laps and call create node if not found
* @id: id of the car
*/

void update_laps(int id)
{
    /*init current to start of the list and found var*/
	Car *current = head;
	bool found = false;

	while (current != NULL)
	{
		if (current->id == car_id)
		{
            /*add a lap*/
			current->laps++;
            /*flag to true*/
			found = true;
            /*we stop browsing in the list*/
			break;
		}
		current = current->next;
	}

    /*if id not found: create a new node*/
	if (!found)
	{
		create_new_car(car_id);
	}
}