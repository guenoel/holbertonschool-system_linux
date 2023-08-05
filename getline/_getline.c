#include "_getline.h"

char *_getline(const int fd)
{
	char *buffer = (char*) malloc(sizeof(char) * READ_SIZE);
	int read_bytes = 0;

	if (buffer == NULL)
		return (NULL);

	read_bytes = read(fd, buffer, READ_SIZE);

	/* End of file */ 
	if (read_bytes == 0)
	{
		free(buffer);
		return (NULL);
	}
	/* If there is an error */
	else if(read_bytes == -1)
	{
		printf("ERROR while readning the line\n");
		return (NULL);
	}



	return (buffer);
}