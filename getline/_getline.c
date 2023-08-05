#include "_getline.h"
char *_getline(const int fd)
{
	int read_bytes = 0;
	int i = 0;
	static int cursor;
	store_t *current = NULL;
	static store_t *first_line_storage;
	char *buffer = (char*) malloc(sizeof(char) * READ_SIZE);
	char *returnedLine;
	store_t *tmp = NULL;

	if (buffer == NULL)
	{
		return (NULL);
	}

	read_bytes = read(fd, buffer, READ_SIZE);

	if (read_bytes == 0 && first_line_storage != NULL)
	{
		// On copie la ligne pour retourner la ligne a afficher
		returnedLine = strdup(first_line_storage->line);
		
		// Permet de liberer plus tard le node une fois qu'on a avancé
		tmp = first_line_storage;
		// On incremente au prochain node pour afficher
		first_line_storage = first_line_storage->next;

		free(tmp->line);
		free(tmp);

		return (returnedLine);
	}
	/* End of file */ 
	if (read_bytes == 0)
	{
		free(buffer);
		return (NULL);
	}
	/* If there is an error */
	else if(read_bytes == -1)
	{
		printf("ERROR while reading the line\n");
		return (NULL);
	}

	current = first_line_storage;
	/* Implement a queue */
	while(buffer[i] != '\0')
	{
		for (cursor = i; buffer[cursor] != '\n' && buffer[cursor] != '\0'; cursor++)
			;

		if (first_line_storage == NULL)
		{
			first_line_storage = new_node(&first_line_storage, buffer, cursor - i);
			continue;
		}

		while (current->next)
			current = current->next;

		current->next = new_node(&first_line_storage, buffer, cursor - i);
	
	}

	if (first_line_storage == NULL)
		return (NULL);

	// On copie la ligne pour retourner la ligne a afficher
	returnedLine = strdup(first_line_storage->line);
	
	// Permet de liberer plus tard le node une fois qu'on a avancé
	tmp = first_line_storage;
	// On incremente au prochain node pour afficher
	first_line_storage = first_line_storage->next;

	free(tmp->line);
	free(tmp);

	return (returnedLine);
}

store_t *new_node(store_t **head, char *buffer, int len)
{
	store_t *new_node = NULL;
	int i = 0;
	
	new_node = (store_t*)malloc(sizeof(store_t));
	new_node->next = NULL;
	new_node->line = (char*)malloc(sizeof(char) * (len + 1));
	
	for (i = 0; buffer[i] != '\n' && buffer[i] != '\0'; i++)
		new_node->line[i] = buffer[i];
	
	new_node->line[i] = '\0';
	new_node->size = i;

	if (head == NULL)
	{
		head = &new_node;
		return (NULL);
	}

	return (new_node);
}