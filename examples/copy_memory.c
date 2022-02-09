/*
	Copying memory in C
*/

#include	<stdio.h>
#include	<string.h>


typedef struct node {
	unsigned int isValid = 1;
	unsigned int size = 15;
	struct node * next;
} node_t;


#define BUFOFFSET	10

int main() {

	node_t n = { .isValid = 1, .size = 367, .next = NULL };
	node_t n2, n3;

	/*
		An inexperienced C programmer may do:

			n2.isValid = n.isValid;
			n2.size = n.size;
			n2.node = n.node;


		An experienced programmer knows they can do:

			n2 = n;

		Another way is using memcpy()
	*/

	memcpy(&n2, &n1, sizeof(node_t);

	/* 
		memcpy() really shines when you want to copy data
		from one place to another where you have less
		structure in mind
	*/

	char buffer[4096];	// maybe part of a network packet?

	/* 
		imagine we want to copy node n into a particular
		location in a buffer
	*/

	memcpy(buffer + BUFOFFSET, &n, sizeof(node_t));

	n3 = buffer + BUFOFFSET;

	printf("n2 = %d, %d, %p\n", n3->isValid, n3->size, n3->next);

	return 0 ;
}


/*
	We can also use memset() to initialize a block of memory
	to a value

		memset(buffer, 0, BUFFER_SIZE);
*/
