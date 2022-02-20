

                 /* INFINITE INPUT BUFFER IN C */


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


int main () {

	int size = 2;

	int *buffer = malloc(size*sizeof(int));

	int input = 0;
	int numdata = 0;

	while (true) {
		if (numdata == size) {
			size *= 2;
			buffer = realloc(buffer, sizeof(int), *size);
		}
		printf("Enter: ");
		scanf("%d", &input);
		if (input == -1)	break;
		else 	buffer[numdata++] = input;
	}

	int total = 0;

	for (int i=0 ; i < numdata ; i++) {
		printf("buffer[%d] = %d\n",i,buffer[i]);
		total += buffer[i];
	}

	printf("Average: %d\n", total/numdata);
	printf("Numdata: %d\n", numdata);
	printf("Buffersize: %d\n", size);

	return 0;
}

