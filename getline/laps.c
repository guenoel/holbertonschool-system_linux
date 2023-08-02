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
	exit(0);
}

for (i = 0; i < size; i++)
{
	update_laps(id[i]);
}

printf("Race state:\n");
/*init current to the start of the list*/
current = head;
while (current != NULL)
{
	printf("Car %d [%d laps]\n", current->id, current->laps);
	current = current->next;
}
}

/**
* update_laps - update laps and call create node if not found
* @id: id of the car
*/

void update_laps(int id)
{
	/*init current to start of the list and found var*/
	car_t *current = head;
	bool found = false;

	while (current != NULL)
	{
		if (current->id == id)
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
		add_new_node(id);
		printf("Car %d joined the race\n", id);
	}
}

void add_new_node(int id)
{
	/*create and fill new node (except next var)*/
	car_t *new_node = (car_t *)malloc(sizeof(car_t));

		if (new_node == NULL)
		{
			fprintf(stderr, "Memory allocation error\n");
			exit(EXIT_FAILURE);
		}
	new_node->id = id;
	new_node->laps = 0;

	/*If list haven't any node or id of first node is bigger that the id*/
	if (head == NULL || head->id > id)
	{
		/*it will be NULL if list is empty*/
		new_node->next = head;
		/*new_node car is on top of the list*/
		head = new_node;
	}
	else
	{
		/*init current var to start of the list*/
		car_t *current = head;
		/*find right position in the list*/
		while (current->next != NULL && current->next->id <= id)
		{
			current = current->next;
		}
		/*init next var after new_node*/
		new_node->next = current->next;
		/*init next var before new_node*/
		current->next = new_node;
	}
}

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
