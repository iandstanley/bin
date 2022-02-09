#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define	PORT	5555


void main() {

	int client_socket; 	// fd returned by socket
	struct sockaddr_in serverAddr;
	char buf[1024];

	client_socket = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serverAddr, '\0', sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(client_socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

	recv(client_socket, buf, 1024, 0);

	printf("%s", buf);

	close(client_socket);
}



