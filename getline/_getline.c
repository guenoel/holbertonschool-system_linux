#include "_getline.h"

/**
 * _getline - return a line from a fd next by next
 * @fd: file descriptor
 * Return: string of a line
 */

char *_getline(const int fd)
{
	int read_bytes = 0;
	int i = 0;
	store_t *current = NULL;
	static store_t *first_line_storage;
	char *line = NULL;
	static int size;
	store_t *tmp1 = NULL;
	store_t *tmp2 = NULL;
	char *print_line;
	char *buffer = (char *) malloc(READ_SIZE * sizeof(char));

	if (buffer == NULL)
	{
		return (NULL);
	}
	init_string(buffer, READ_SIZE);

	if (!first_line_storage)
	{
		first_line_storage = new_node(0);
	}

	if (!first_line_storage->line_finished)
	{
		read_bytes = read(fd, buffer, READ_SIZE);

		/* End of file */
		if (read_bytes == 0 && first_line_storage->size == 0)
		{
			free_node(first_line_storage);
			free(buffer);
			return (NULL);
		}
		/* If there is an error */
		if (read_bytes == -1)
		{
			free_node(first_line_storage);
			free(buffer);
			return (NULL);
		}

		current = first_line_storage;
		line = (char *) malloc(sizeof(char) * READ_SIZE);

		while (buffer[i] != '\0')
		{
			line[size] = buffer[i];
			size++;
			if (buffer[i] == '\n')
			{
				/* -1 to overwrite \n by \0 */
				line[size - 1] = '\0';
				/*first loop - current node already exist*/
				/*est-ce la bonne size ?*/
				if (tmp1 != NULL)
					current = new_node(size);

				current->line = (char *)realloc(current->line, sizeof(char) * size);
				init_string(current->line, size);
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
				/*est-ce la bonne size ?*/
				if (tmp1 != NULL)
					current = new_node(size);
				current->line = (char *)realloc(current->line, sizeof(char) * (size + 1));
				init_string(current->line, (size + 1));
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
	free(buffer);

	print_line = strdup(first_line_storage->line);

	/*save pointer of first node, update new first and free old first node*/
	tmp2 = first_line_storage;
	first_line_storage = first_line_storage->next;
	free_node(tmp2);

	return (print_line);

}

/**
 * new_node - create a new node with empty init variables
 * @len: size of string
 *
 * Return: pointer to the new node
 */

store_t *new_node(unsigned int len)
{
	store_t *new_node = NULL;

	new_node = (store_t *)malloc(sizeof(store_t));
	new_node->next = NULL;
	new_node->line = (char *)malloc(sizeof(char) * (len + 1));
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
	if (str == NULL)
		return (false);

	while (*str != '\0')
	{
		if (*str == c)
			return (true);
		str++;
	}

	return (false);
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

/**
 * init_string - init memory to null
 * @string: string to erase
 * @size: size to erase
 */

void init_string(char *string, int size)
{
	int j;

	for (j = 0; j < (size); j++)
	{
		string[j] = '\0';
	}
}