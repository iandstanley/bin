
/*
	POTENTIAL SECURITY VULNERABILITY IN REALLOC() IN C

	When you use realloc() to dynamically reallocate a greater
	amount of memory for something that you already have on the
	heap already.

	What can happen is that realloc() can copy that data to an
	entirely new place in memory (if it cannot simply extend).
	If this occurs, the original location in memory will still
	contain the pre-extended data where other programs could
	potentially access. This could be a security vulnerability
	for sensitive data.


	Memory:

		other
	var:	password1      	password2
	data:	a b c 1 2 3 \0 	x y z 1 2 3 \0
	mem:	0 1 2 3 4 5  6 	7 8 9 a b c  d
			     ^               ^
			     +-- NULL        +-- NULL

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {

	char *password1;
	char *password2;
	char *other;

	password1 = malloc(7 * sizeof(char));
	password2 = malloc(7 * sizeof(char));

	strcpy(password1, "abc123");
	strcpy(password2, "xyz789");

	/*
		Because we have only just started the program, the
		malloc() for password2 will allocate contigously
		in memory right after malloc() for password1. See
		above diagram in comment
	*/

	printf("password1 addr = %p\npassword2 addr = %p\n",
		password1, password2);


	/* or as integer output */

	printf("password1 addr = %d\npassword2 addr = %d\n",
		(int) password1, (int) password2);


	/* We see that they are very close in memory */

	for (int i=0; i < 100; i++) 
		printf("%c", password1[i]);

	printf("\n");


	/*
		Let's say the size of password1 has to be changed
		- maybe the user chose a longer password

		If we try to realloc() password1, realloc() will
		be forced to copy *password1 to another location
		in memory where there is more space

		Let's examine the memory by saving the memory address
		of password1 to another pointer
	*/

	other = password1; 

	password1 = realloc(password1, 20 * sizeof(char));

	printf("password1 = %s\n", password1);

	/* 
		we see realloc() has copied contents of password1
		to a new location
	*/

	printf("password1 addr = %p\npassword2 addr = %p\n",
		password1, password2);

	/*
		notice password1 address is changed to a location
		where there is room for the 20 characters requested
	*/

	printf("other addr = %p\n", other);

	/*
		as realloc() didn't clear space we can still access
		it
	*/

	printf("string at other ptr = %s\n", other);

	/*
		this can be a problem say if you get a memory dump
		of program
	*/

	for (int i; i < 100; i++)
		printf("%c", other);

	printf("\n");

	/*
		as realloc() deallocates the old memory it is
		available for other programs to allocate!
	*/

}


