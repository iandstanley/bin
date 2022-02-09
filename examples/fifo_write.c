/*
	Using a FIFO to communicate betwwen processes in C

	The user will need to create the fifo "sum" in the current
	directory

		$ mkfifo sum
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<sys/stat.h>
#include	<sys/types/h>
#include	<errno.h>
#include	<fcntl.h>


	/* write to FIFO */

int main() {

	int arr[5];

	srand(time(NULL));

	for (int i=0; i < 5; i++)
		arr[i] = rand() % 100;

	int fd = open("sum", O_WRONLY);

	if (fd == -1)	return 1;

	if ( write(fd, arr, sizeof(int) * 5) == -1)
		return 2;

	close(fd);

	return 0;
}

