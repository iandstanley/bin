#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


#define	CL_QUEUE	6
#define	PORT 		5555

void main() {

	int sockfd;
	struct sockaddr_in serverAddr; 
	int newsocket;
	struct sockaddr_in newAddr; 	// client

	socklen_t addr_size;
	char buf[1024];

	sockfd = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serverAddr, '\0', sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

	listen(sockfd, CL_QUEUE);	// typically put in a while(1) loop

	newsocket = accept(sockfd, (struct sockaddr *)&newAddr, &addr_size);

	strcpy(buf, "Hello from server\n");

	send(newsocket, buf, strlen(buf), 0);

	close(newsocket);
}


