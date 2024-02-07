#include "socket.h"

/* Assuming IPv4 o IPv6 addresses */
#define BUFFER_SIZE 46

/**
* initialize_Server - Initialize the server
* @server_conf: Server address structure
* @server_socket_fd: Server socket
*/
void initialize_Server(struct sockaddr_in *server_conf, int *server_socket_fd)
{
	/* Initialize server_conf structure */
	memset(server_conf, 0, sizeof(*server_conf));

	/* Create socket */
	*server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (*server_socket_fd == -1)
	{
		perror("Failed to create socket");
		exit(EXIT_FAILURE);
	}

	/* Configure the server address structure */
	server_conf->sin_family = AF_INET; /* AF_INET -> IPv4:port */
	server_conf->sin_addr.s_addr = htonl(INADDR_ANY);
	server_conf->sin_port = htons(12345);

	/* Bind socket to address and port */
	if (bind(*server_socket_fd, (struct sockaddr *)server_conf,
		sizeof(*server_conf)) < 0)
	{
		perror("Failed to bind socket");
		exit(EXIT_FAILURE);
	}

	/* Listen for incoming connections */
	if (listen(*server_socket_fd, 1) < 0)
	{
		perror("Failed to listen for incoming connections");
		exit(EXIT_FAILURE);
	}

	/* Print server information */
	printf("Server listening on port 12345\n");
}

/**
* accept_Connection - Accept incoming connections
* @server_socket_fd: Server socket
*/
void accept_Connection(int server_socket_fd)
{
	while (1)
	{
		struct sockaddr_in client_addr;
		socklen_t client_addr_len = sizeof(client_addr);
		int client_socket;
		/* Buffer to store the client's IP address */
		char client_ip[INET6_ADDRSTRLEN];

		/* Accept incoming connection : create new socket for client and */
		/* store infos in it */
		client_socket = accept(server_socket_fd, (struct sockaddr *)&client_addr,
								&client_addr_len);
		if (client_socket < 0)
		{
			perror("Failed to accept incoming connection");
			exit(EXIT_FAILURE);
		}

		/* Convert client IP address to display format */
		if (inet_ntop(AF_INET, &client_addr.sin_addr, client_ip,
						INET6_ADDRSTRLEN) == NULL)
		{
			perror("Inet_ntop failed");
			exit(EXIT_FAILURE);
		}

		/* Print the client's IP address */
		printf("Client connected: %s\n", client_ip);

		/* Close the connection */
		close(client_socket);
	}
}

/**
* main - Entry point
* Return: 0 on success, 1 on failure
*/
int main(void)
{
	int server_socket_fd;
	struct sockaddr_in server_conf;

	/* Initialize the server */
	initialize_Server(&server_conf, &server_socket_fd);

	/* Accept incoming connections continuously */
	accept_Connection(server_socket_fd);

	/* Note: The server will not reach this point in current implementation */
	close(server_socket_fd);

	return (0);
}
