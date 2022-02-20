
        /* HEAP INSPECTION SECURITY VULNERABILITY IN C */

/*
	We are going to find that free() doesn't clear the dyanmically
	allocated memory contents.
*/


#include <stdio.h>
#include <stdlib.h>

int main() {

	char* password;
	char* other;

	password = malloc(10 * sizeof(char));

	printf("Trustworthy program/enter password: ");
	scanf("%s", password);

	other = password;

	free(password);

	/* all free() does is mark memory as available to reallocate */


	for (int i=0; i<10; i++)
	printf("%c", other[x]);

}


/*

	This is a security vulnerability because your program could
	be dumped eg 'kill -SEGV PID' and your password would be
	dumped as well.

	You could also use malloc to allocate space and potentially
	find that sensitive data.

	We may want to encrypt the data before storing it on the
	heap or zero the memory out BEFORE free() is called.

*/


