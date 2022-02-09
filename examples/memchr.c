/*
                          MEMCHR() IN C
 
	memchr() finds the first occurance of a character in a
	character array.
*/


#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {

	char data[] = { 'q', 'r', 's', 't', 'p', 'a', 'x' };

	char* pos = memchr( data, 't', sizeof data );

	assert( pos != NULL );	 

	pos = memchr( data, 'z', sizeof data );

	assert( pos == NULL );	  // z not found

	pos = memchr( data, 'p', 3 );	// find p in first 3 chars

	assert( pos == NULL );	 


	char str[] = "john.smith@microsoft.com";

	char * domain = memchr(str, '@', sizeof str);

	/*
		domain now contains '@microsoft.com' so we can print
		just the domain with &domain[1]
	*/

	printf("domain = %s\n", &domain[1]);
}

