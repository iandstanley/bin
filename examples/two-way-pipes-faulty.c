#include	<stdio.h>
#include	<stdlib.h>
#include	<sys/wait.h>
#include	<unistd.h>

/*
	Simple problem: generates a number from 0..9 and sends the
	number to the other process. That process multiplies the
	received no by 4 and sends results back.
*/

int main () {

	int p1[2];

	if (pipe(p1) == -1) { return 1; }

	int pid = fork();
	if (pid == -1) { return 2; }

	if (pid == 0) {
		// child process

		int x;
		if (read(p1[0], &x, sizeof(x)) == -1) { return 3; }

		printf("Received %d\n", x);
		x *= 4;

		if (write(p1[1], &x, sizeof(x)) == -1) { return 4; }
		printf("Wrote %d\n", x);

	} else {
		// parent process
		srand(time(NULL));

		int y = rand() % 10;

		if (write(p1[1], &y, sizeof(y)) == -1) { return 5; }

		/* 
			if the following printf is commented out
			parent reads the no back again. Why? Well
			printf to the terminal is slow and the
			kernel switches out to the other process
			whilst waiting for the kernel to handle the
			I/O request
		*/
		printf("Wrote %d\n", y);

		if (read(p1[0], &y, sizeof(y)) == -1) { return 6; }
		printf("Result = %d\n", y);

		wait(NULL);
	}

	close(p1[0]);
	close(p1[1]);

	return 0;
}

