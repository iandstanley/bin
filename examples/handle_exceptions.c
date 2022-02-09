/*
 * HANDLING EXCEPTIONS IN C
 * - a but like try...catch
 *
 * setjmp(3) saves a progam's computing context (a bit like a
 * snapshot) saving a specific context that we can later jump back
 * to with longjmp(3)
 *
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<setjmp.h>


jmp_buf savebuf;	// buffer to store context 


double compute_arg(double *values, size_t length) {

	double sum = 0;

	if (length<=0) {
		/* create exception and return with setjmp()=1 */
		longjmp(savebuf, 1);
	}

	for (int i=0; i<length; i++) {
		sum += values[i];
	}

	return sum/(double) length;
}

int main(int argc, char **argv) {

	int arrlength = argc - 1;
	double *darr = malloc(sizeof(double)*arrlength);

	for (int i=1; i<argc; i++) {
		darr[i-1] = atof(argv[i]);
	}

	if (setjmp(savebuf) == 0) {

		/* save program context and initially return 0 */

		double avg = compute_avg(darr, arrlength);
		printf("Average = %lf \n", avg);

	} else {

		/* equivalent of catch block */

		printf("ERROR: invalid input!");
	}
}


/*

We could:

	#define	TRY		if(setjmp(savebuf) == 0)
	#define	CATCHALL	else


Which would give us:

	TRY {
		double avg = compute_avg(darr, arrlength);
		printf("Average = %lf \n", argv);
	}
	CATCHALL {
		printf("ERROR: Invalid input\n");
	}





We could also:

	int exceptionval = 0;

	#define	TRY		if((exceptionval = setjmp(savebuf)) == 0)
	#define	CATCH(NUM)	else if (exceptionval == NUM)
	#define	CATCHALL	else
	#define	THROW(NUM)	longjmp(savebuf, NUM)

So we can have:

	if (length <=0) {
		THROW(1);
	}

	CATCH(1) { printf("I got error 1\n"; }

*/


