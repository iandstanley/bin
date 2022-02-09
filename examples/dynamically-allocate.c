
      /* DYNAMICALLY ALLOCATE MEMORY FOR ARRAY OF STRINGS */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define	BUFFER_SIZE	4096

int main() {

	char ** strings;

	/* lets allocate memory in 2 steps */

	int total = 0;

	printf("Enter no of strings: ");

	scanf("%d", &total);

	strings = malloc(total * sizeof(char *));

	/* allocate as we get each string */

	char buffer[BUFFER_SIZE];
	int length = 0;


	while (getchar() != '\n'); 	// flush stdin

	printf("\n");

	for (int i=0 ; i < total ; i++) {

		printf("Enter string %d: ", i+1);

		fgets(buffer, BUFFER_SIZE, stdin);

		length = strlen(buffer);

		/* fgets stores the '\n' enter into buffer */

		buffer[length-1] = '\0';

		strings[i] = malloc( length * sizeof(char));

		/* 
			note we use length rather than length+1 as
			we moved the '\0' left
		*/

		strcpy(strings[i], buffer);
	}


	for (int i=0 ; i < total ; i++) 
		printf("strings[%d] = %s\n", i, strings[i]);

}


