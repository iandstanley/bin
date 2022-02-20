#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <assert.h>

#define THERE_WAS_NO_YEAR_0 1

/*	
	Examples isleap1 to isleap5 and non-C programs
	taken from "The Forgotten Art of Structured Programming" by Kevlin Henney

*/

int isleap1(year)
int year;
{
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

int isleap2(year)
int year;
{
	if (year % 400 == 0)
		return 1;
	if (year % 100 == 0)
		return 0;
	if (year % 4 == 0)
		return 1;
	return 0;
}

int isleap3(year)
int year;
{
	if (year % 400 == 0)
		goto true;
	if (year % 100 == 0)
		goto false;
	if (year % 4 == 0)
		goto true;
false:
	return 0;
true:
	return 1;
}

int isleap4(year)
int year;
{

	if (!(year % 400)) goto true;

	if (!(year % 100)) goto false;

	if (!(year % 4)) goto true;
false:
	return 0;
true:
	return 1;
}

int isleap5(year)
int year;
{
	if (!(year % 400))
true:		return !0;
	if (!(year % 100))
false:		return 0;
	if (!(year % 4))
		goto true;
	goto false;
}



/*
	and a couple of my versions
*/
int isleap6(year)
int year;
{
	int offset;
	int ret;
	char * yearstring;

        if (year <= 0) {
		errno = EDOM;
		return 0;
	}

	yearstring = malloc(6*sizeof(char));
	
	sprintf(yearstring,"%d", year);
	offset = ((int)log10(year) +1) -2 ;	/* +1 to fix log10 origin, +2 to skip to tens of years*/

	ret =  1 &&  !strcmp(yearstring+offset,"00") ? ! (year % 400)   : year ?  !(year % 4) : 0 ; 
	free(yearstring);
	return ret;
}


int isleap7(year)
int year;
{
        if (year == 0) errno = EDOM;

	return year % 100 ? year == (year>>2<<2) : (year * ! (year % 400)) && 1;
}


int main() {

	int testcases[] = { 6004, 2021, 2020, 2000, 1985, 1968, 1944, 1900, 1812, 1800, 1600, 999, 996, 99, 60, 0 };
	int actual_result[] = { 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };
	int no_testcases = sizeof(testcases) / sizeof(int);
	int i; 

	assert(THERE_WAS_NO_YEAR_0 == 1);   /* USING A PARADIGM OF NO YEAR ZERO */
	
	printf("Testing  %d testcases\n", no_testcases);

	printf("Function:	year  isleap1  EXPECTED\n");

	for (i = 0; i < no_testcases ; i ++ ){

		printf("result: %12d %12d\n", isleap1(testcases[i]), actual_result[i]);

	}
	printf("\n\n Year 0 is not a leap year because year 0 didn't exist\n\n");
	printf("I suppose technically the function ought to have an\nassert(year != 0); and some other logic ...\n");

	return 0;
};



/*


	In FORTRAN66:

		FUNCTION ISLEAP(YEA)
		LOGICAL ISLEAP
		INTEGER YEAR
		IF (MOD(YEAR,400) .EQ. 0) GOTO 20
		IF (MOD(YEAR,100) .EQ. 0) GOTO 10
		IF (MOD(YEAR,4) .EQ. 0) GOTO 20
	10	ISLEAP = .FALSE.
		RETURN
	20	ISLEAP = .TRUE.
		RETURN


	Note some programmers changed the code after line 10 to:

		GOTO 30
	20	ISLEAP = .FALSE.
		GOTO 30
	30 	CONTINUE
		RETURN
		END




	In ALGOL68

		proc is leap yar = (int year) bool:

			if year mod 400 = 0 then 
				true
			elif year mod 100 = 0 then 
				false
			elif year mod 4 = 0 then
				true
			else
				false
			fi;









	The DAS DEVICE (example of multi-entrant code in C):

		send(to, from, count)
		register short *to, *from;
		register count;
		{
			register n = (count+7)/8;
			switch (count % 8 ) {
				case 0:		do {	*to = *from++;
				case 7:			*to = *from++;
				case 6:			*to = *from++;
				case 5:			*to = *from++;
				case 4:			*to = *from++;
				case 3:			*to = *from++;
				case 2:			*to = *from++;
				case 1:			*to = *from++;
					} while (--n>00;
			}
		}

	This re-entrant C code is from a telecoms application.

		"I feel a combination of pride and revulsion at this discovery" 
							~ Tom Duff

		"Many people have said the worst feature of C is that switches don't break
		automatically before each case statement. This code forms some sort of 
		arguement in that debate, but I am not sure whether it is for or against."
							~ Tom Duff

	Sometimes we pick up the advice of:

		"A function should only have a single return"

	But the problem is that this applies only to FORTRAN66 and doesn't really apply to
	almost all other languages (ie Algol/X based languages).

	The problem with the return statement is that it violates the "single responsibility 
	rule" as it does two things: (1) return binds a value to the result of a function,
	
*/
