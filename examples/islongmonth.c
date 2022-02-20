#include <stdio.h>


int islongmonth(m) {
	return m <8 ? m != m>>1<<1  : m == m>>1<<1 ;
}

int islongmonth2(m) {
	return (int[]){0,1,0,1,0,1,0,1,1,0,1,0,1}[m];
}

int islongmonth3(m) {
	return m&1<<3 ? (-1^m)&1 : m&1;
}

int main() {

	int month;
	char *months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
			"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

	printf("Long and short months\n\n");

	printf("Method:	%12s %12s %12s\n", "bitwise", "anonymous", "logic");
	printf("Used   	%12s %12s %12s\n\n", "", "array", "logic");

	for (month=1 ; month <=12 ; month ++) {

		printf("%s:    %12s %12s %12s\n", 
			months[month-1], 
			islongmonth(month) ? "true" : "false",
			islongmonth2(month) ? "true" : "false",
			islongmonth3(month) ? "true" : "false" );
	}
}



/*

	In FORTRAN 66


		FUNCTION ISLEAP(YEAR)
		LOGICAL ISLEAP
		INTEGER YEAR
		IF (MOD(YEAR,400) .EQ. 0) GOTO 20
		IF (MOD(YEAR,100) .EQ. 0) GOTO 10
		IF (MOD(YEAR,4) .EQ. 0) GOTO 20
	10	ISLEAP = .FALSE.
		RETURN
	20	ISLEAP = .TRUE.
		RETURN


	Some programmers get nervous about the RETURN  without seeing an END and change the return after line 10 to the following:

		GOTO 30
	20	ISLEAP = .TRUE.
	30	RETURN
		END

	Or even:

		GOTO 30
	20	ISLEAP = .FALSE.
		GOTO 30 
	30	CONTINUE
		RETURN
		END


*/
