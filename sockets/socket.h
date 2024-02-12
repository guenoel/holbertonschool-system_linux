#ifndef _SOCKET_
#define _SOCKET_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
/* Include for inet_ntoa */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <ctype.h>

struct addrinfo
{
    int ai_family;
    int ai_socktype;
    int ai_protocol;
    socklen_t ai_addrlen;
    struct sockaddr *ai_addr;
    struct addrinfo *ai_next;
};

#endif /* _SOCKET_*/
