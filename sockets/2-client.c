#include "socket.h"

/**
* connect_to_server - Connect to the server using provided host and port
* @host: Host address
* @port: Port number
* Return: Socket file descriptor on success, -1 on failure
*/
int connect_to_server(char *host, char *port)
{
	int client_socket_fd;
	struct addrinfo hints, *res, *curr_res;

	/* Initialize hints structure */
	memset(&hints, 0, sizeof(struct addrinfo));
	/* Set up hints data structure */
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	/* Resolve host name to IP address */
	if (getaddrinfo(host, port, &hints, &res) != 0)
	{
		fprintf(stderr, "Invalid host address: %s\n", host);
		return (-1);
	}
	/* Iterate through the list of addresses and try to connect */
	for (curr_res = res;
		curr_res != NULL;
		curr_res = curr_res->ai_next)
	{
		client_socket_fd = socket(curr_res->ai_family, curr_res->ai_socktype,
									curr_res->ai_protocol);
		if (client_socket_fd == -1)
			continue;

		if (connect(client_socket_fd, curr_res->ai_addr,
										curr_res->ai_addrlen) != -1)
			break; /* Successfully connected */
		close(client_socket_fd);
	}
	/* Check if connection was successful */
	if (curr_res == NULL)
	{
		perror("Connection failed");
		return (-1);
	}
	/* Free the memory allocated by getaddrinfo */
	freeaddrinfo(res);

	return (client_socket_fd);
}

/**
* main - Entry point
* @argc: Argument count
* @argv: Argument vector
* Return: 0 on success, 1 on failure
*/
int main(int argc, char *argv[])
{
	int server_socket_fd;
	int port = 0;
	void *host = NULL;

	/* Check command-line arguments */
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Check convertion host to binary format */
	if (inet_pton(AF_INET, argv[1], host))
	{
		perror("Failed to convert host to binary format");
		exit(EXIT_FAILURE);
	}
	/* Check convertion port to integer */
	port = atoi(argv[2]);
	if (!port)
	{
		perror("Failed to convert port to integer");
		exit(EXIT_FAILURE);
	}

	/* Connect to the server */
	server_socket_fd = connect_to_server(argv[1], argv[2]);

	/* Check if connection was successful */
	if (server_socket_fd == -1)
		exit(EXIT_FAILURE);

	/* Connection successful */
	printf("Connected to %s:%s\n", argv[1], argv[2]);

	/* Note: The server will not reach this point in curr implementation */
	close(server_socket_fd);

	return (0);
}
