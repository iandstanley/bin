/*
	reseeding_srand.c

	If a program runs srand() multiple times per second, would
	we be seeding the random number gernerator with the same
	value?
*/


#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <unistd.h>

int main() {

/* 
	The following line is typically used to init the seed for
	srand()

	srand(time(NULL));

	If we run this program repeatedly using the line above
	rather than the lower line  we will see that we get the
	same random number repeated.  A better way is as follows:
*/
	srand(time(NULL) * getpid() );

	int rand_val = rand();

	printf("%d\n", rand_val); return 0;
}

