#ifndef	_MYQUEUE_H
#define	_MYQUEUE_H

struct node {
	struct node* next;
	int *client_socket;
};
typedef struct node node_t;


void enqueue(int * client_socket);
int * dequeue();

#endif
