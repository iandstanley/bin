#include	<stdio.h>
#include	<stdlib.h>
#include 	<string.h>
#include	<unistd.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<stdbool.h>
#include	<limits.h>
#include	<pthread.h>

/*
 * We are going to use a queue to handle incoming connections with
 * each connection being passed onto a pthread to handle the return
 * data transfer
 */
#include	"myqueue.h"

#define		SERVERPORT	8989
#define		BUFSIZE		4096
#define		SOCKETERROR	(-1)
#define		SERVER_BACKLOG	100

typedef struct	sockaddr_in	SA_IN;
typedef struct	sockaddr	SA;

/*
 * Pthreads are used to have multiple processes handling connections
 * to improve throughput.  A mutex is used to provide a locking mechanism
 * to prevent simultaneous threads overwriting each other's data
 */

pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t	condition_var = PTHREAD_COND_INITIALIZER;

#define		THREAD_POOL_SIZE	20
pthread_t	thread_pool[THREAD_POOL_SIZE];

void * 	thread_function(void * msg);
void * 	handle_connection(void * client_socket);
int	check(int exp, const char *msg);


int main (int argc, char **msg) {

	int 	server_socket, client_socket, addr_size;
	SA_IN	server_addr, client_addr;


	for (int i = 0; i <  THREAD_POOL_SIZE; i++) {
		pthread_create(&thread_pool[i], NULL, thread_function, NULL);
	}

	check(( server_socket = socket(AF_INET, SOCK_STREAM, 0)), 
		"Failed to create socket");

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(SERVERPORT);

	check( bind(server_socket, (SA*)&server_addr, sizeof(server_addr)), 
		"Bind Failed");

	check( listen(server_socket, SERVER_BACKLOG), "Listen Failed");

	while (true) {

		printf("Waiting for connections...\n");

		addr_size = sizeof(SA_IN);

		/* get connection */
		check( client_socket = accept(server_socket, 
			(SA*)&client_addr, (socklen_t*)&addr_size), 
			"Listen failed");

		printf("Connected.\n");

	/*
	 * We need to put connection info somewhere so that an available thread
	 * can find it. We will use a queue (client_queue.c) to handle this
	 */

		int *pclient = malloc(sizeof(int));

		pthread_mutex_lock(&mutex);

		*pclient = client_socket;

		enqueue(pclient);

		pthread_cond_signal(&condition_var);

		pthread_mutex_unlock(&mutex);
	}

	return 0;
}


int check(int exp, const char *msg) {
	
	if (exp == SOCKETERROR) {
		perror(msg);
		exit(1);
	}
	return exp;
}



void * handle_connection(void * p_client_socket) {

	int 	client_socket = *((int*) p_client_socket);
	free(p_client_socket);		// not needed anymore

	char 	buffer[BUFSIZE];
	size_t	bytes_read;
	int	msgsize = 0;
	char 	actualpath[PATH_MAX +1];

	// read client msg - name of file to read

	while (( bytes_read = read( client_socket, buffer + msgsize, sizeof(buffer) - msgsize - 1 )) > 0 ) {

		msgsize += bytes_read;
		
		if (msgsize > BUFSIZE -1 || buffer[msgsize - 1] == '\n') break;
	}

	check(bytes_read, "recv error");

	buffer[msgsize - 1] = 0;	// null terminate and remove '\n'

	printf("REQUEST: %s\n", buffer);

	fflush(stdout);

	/*
	 * SECURITY NOTE
	 * 
	 * This example server is a simple implementation and suffers from no
	 * restrictions on the file requested other than the standard unix
	 * file perms.
	 * 
	 * This server is currently vulnerable to slow connections attacks
	 * in a DOS situation
	 *
	 */

	if (realpath(buffer, actualpath) == NULL ) {
		printf("ERROR (bad path): %s\n", buffer);
	
		close(client_socket);
		return NULL;
	}

	FILE * fp = fopen(actualpath, "r");

	if (fp == NULL) {
		printf("Error (open): %s\n", buffer);

		close(client_socket);
		return NULL;
	}

	while (( bytes_read = fread(buffer, 1, BUFSIZE, fp)) > 0) {
	
		printf("Sending %zu bytes \n", bytes_read);
		write(client_socket, buffer, bytes_read);
	}

	close(client_socket);
	fclose(fp);

	printf("Closing connection\n");
	return NULL;
}


void * thread_function(void *arg) {

	int * pclient;

	while (true) {

		pthread_mutex_lock(&mutex);

		if ( (pclient = dequeue() ) == NULL) {

			pthread_cond_wait(&condition_var, &mutex);

			// try again
			pclient = dequeue();
		}

		pthread_mutex_unlock(&mutex);

		if (pclient != NULL) {
			handle_connection(pclient);
		}	
	}

}


