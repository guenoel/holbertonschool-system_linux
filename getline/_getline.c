#include "_getline.h"
char *_getline(const int fd)
{
	int read_bytes = 0;
	int i = 0;
	store_t *current = NULL;
	static store_t *first_line_storage;
	char *line = NULL;
	static int size = 0;
	store_t *tmp1 = NULL;
	store_t *tmp2 = NULL;
	char *buffer = (char*) malloc(sizeof(char) * READ_SIZE);
	char *print_line;

	if (buffer == NULL)
	{
		return (NULL);
	}

	if (!first_line_storage)
	{
		first_line_storage = new_node(0);
	}

	//printf("******** DEBUG: line finished ?: %d\n", first_line_storage->line_finished);
	if (!first_line_storage->line_finished)
	{
		//printf("******** DEBUG: ya pas de retour à la ligne ! Voyez: %s\n", first_line_storage->line);
		read_bytes = read(fd, buffer, READ_SIZE);
		/*if no lines in storage and no lines in buffer: fd is finished*/
		/* End of file */ 
		if (read_bytes == 0 && first_line_storage->size != 0)
		{
			free(buffer);
			return (NULL);
		}
		/* If there is an error */
		if(read_bytes == -1)
		{
			//printf("ERROR while reading the line\n");
			return (NULL);
		}

		current = first_line_storage;
		line = (char*) malloc(sizeof(char) * READ_SIZE);
		//printf("******** DEBUG: c'est parti pour un boucle buffer\n");
		while(buffer[i] != '\0')
		{
			line[size] = buffer[i];
			size++;
			if (buffer[i] == '\n')
			{
				/* -1 to overwrite \n by \0 */
				line[size - 1] = '\0';
				/*in this case this is the first loop - current node already exist*/
				if (tmp1 != NULL)
					current = new_node(size); /*est-ce la bonne size ?*/
				
				current->line = (char*)realloc(current->line, sizeof(char) * size);
				if (current->line == NULL)
				{
					printf("Fail to realloc\n");
					exit(1);
				}
				/*concatenate to append line of previous buffer (previous read)*/
				strcat(current->line, line);
				line[0] = '\0';
				current->size = size;
				size = 0;
				current->line_finished = true;
				/*At first loop the node is the only one - it is the head*/
				if (tmp1 != NULL)
					tmp1->next = current;
				tmp1 = current;
			}
			if (buffer[i + 1] == '\0')
			{
				line[size] = '\0';
				if (tmp1 != NULL)
					current = new_node(size); /*est-ce la bonne size ?*/
				current->line = (char*)realloc(current->line, sizeof(char) * size);
				if (current->line == NULL)
				{
					printf("Fail to realloc\n");
					exit(1);
				}
				/*concatenate to append line of previous buffer (previous read)*/
				strcat(current->line, line);
				line[0] = '\0';
				current->size = size;
				/*not init size to 0*/
				current->line_finished = false;
				if (tmp1 != NULL)
					tmp1->next = current;
				tmp1 = current;
			}
			i++;
		}
		if (line)
			free(line);
	}

	// current = first_line_storage;
	// while (current->next != NULL)
	// {
	// 	printf("/*******DEBUG %s\n", current->line);
	// 	current = current->next;
	// }

	print_line = strdup(first_line_storage->line);

	/*save pointer of first node, update new first and free old first node*/
	tmp2 = first_line_storage;
	first_line_storage = first_line_storage->next;
	free_node(tmp2);
	//printf("DEBUG: la 2eme ligne sera: %s\n", first_line_storage->line);

	return(print_line);

}

store_t *new_node(unsigned int len)
{
	store_t *new_node = NULL;
	
	new_node = (store_t*)malloc(sizeof(store_t));
	new_node->next = NULL;
	new_node->line = (char*)malloc(sizeof(char) * (len));
	new_node->line[len] = '\0';
	new_node->size = len;
	new_node->line_finished = false;

	return (new_node);
}

/**
 * is_char_in_str - fonction principale
 * @str: string to check
 * @c: char to compare
 *
 * Return: true if contained, false if not
 */

bool is_char_in_str(const char *str, char c)
{
    if (str == NULL) {
        return false;
    }

    while (*str != '\0') {
        if (*str == c) {
            return true;
        }
        str++;
    }

    return false;
}

/**
 * free_node - Free a node
 * @node: The node
 */
void free_node(store_t *node)
{
		free(node->line);
		free(node);
}