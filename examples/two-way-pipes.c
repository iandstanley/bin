#include	<stdio.h>
#include	<stdlib.h>
#include	<sys/wait.h>
#include	<unistd.h>

/*
	Simple problem: generates a number from 0..9 and sends the
	number to the other process. That process multiplies the
	received no by 4 and sends results back.
*/

#define _INPUT_		0
#define _OUTPUT_	1

int main () {

	int to_parent[2]; 	// to_parent: child => parent
	int to_child[2]; 	// to_child: parent => child

	if (pipe(to_parent) == -1) { return 1; }
	if (pipe(to_child) == -1) { return 1; }

	int pid = fork();
	if (pid == -1) { return 2; }

	if (pid == 0) {
		// child process
		close(to_parent[_INPUT_]);	// we don't read from to_parent[0]
		close(to_child[_OUTPUT_]);	// we don't write to to_child[1]

		int x;
		if (read(to_child[_INPUT_], &x, sizeof(x)) == -1) { return 3; }

		printf("Received %d\n", x);
		x *= 4;

		if (write(to_parent[_OUTPUT_], &x, sizeof(x)) == -1) { return 4; }
		printf("Wrote %d\n", x);

		close(to_parent[_OUTPUT_]);
		close(to_child[_INPUT_]);

	} else {
		// parent process
		close(to_parent[_OUTPUT_]);	// we don't write to to_parent[0]
		close(to_child[_INPUT_]);	// we don't read from to_child[1]

		srand(time(NULL));

		int y = rand() % 10;

		if (write(to_child[_OUTPUT_], &y, sizeof(y)) == -1) { return 5; }

		/* 
			if the following printf is commented out
			parent reads the no back again. Why? Well
			printf to the terminal is slow and the
			kernel switches out to the other process
			whilst waiting for the kernel to handle the
			I/O request
		*/
		printf("Wrote %d\n", y);

		if (read(to_parent[_INPUT_], &y, sizeof(y)) == -1) { return 6; }
		printf("Result = %d\n", y);

		close(to_parent[_INPUT_]);
		close(to_child[_OUTPUT_]);

		wait(NULL);
	}


	return 0;
}

