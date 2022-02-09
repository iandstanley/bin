/*
	Using a FIFO to communicate between processes in C
	Using a FIFO to communicate betwwen processes in C
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<sys/stat.h>
#include	<sys/types/h>
#include	<errno.h>
#include	<fcntl.h>


	/* read from FIFO */

int main() {

	int arr[5];

	srand(time(NULL));

	int fd = open("sum", O_RDONLY);

	if (fd == -1)	return 1;

	if ( read(fd, arr, sizeof(int) * 5) == -1)
		return 2;

	close(fd);

	int sum = 0 ;

	for (int i= 0l i < 5; i++) 
		sum += arr[i];

	printf("Result is %d\n", sum);

	return 0;
}

