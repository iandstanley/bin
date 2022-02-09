#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<sys/wait.h>
#include	<errno.h>

/*
	A PRACTICAL USE OF FORKS AND PIPES

	Here we want to split up the work into two processes to
	divide and conquer the massive calculation problem ;)
*/


int main() {

	int arr[] = { 1, 2, 3, 4, 1, 2 };
	int arrSize = sizeof(arr) / sizeof(int);
	int start, end;
	int fd[2];


	if (pipe(fd) == -1) { return 1;}

	int id = fork();
	if (id == -1) { return 2; }

	if (id == 0) {
		start = 0;
		end = arrSize / 2;
	} else {
		start = arrSize /2;
		end = arrSize;
	}

	int sum = 0;

	for (int i = start; i < end; i++) {
		sum += arr[i];
	}

	printf("Calculated partial sum: % d\n", sum);

	if (id == 0) {
		// child process
		close(fd[0]);

		if (write(fd[1], &sum, sizeof(sum)) == -1) {
			return 3;
		}
		close(fd[1]);
	} else {
		// parent process
		close(fd[1]);

		int sumFromChild;

		if(read(fd[0], &sumFromChild, sizeof(sumFromChild)) == -1) {
			return 4;
		}
		close(fd[0]);

		int TotalSum = sum + sumFromChild;

		printf("Total sum is %d\n", TotalSum);

		wait(NULL);
	}

	return 0;

}


