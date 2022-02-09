
	/* DELETE ALL OCCURANCES OF A SUBSTRING FROM A STRING */


#include <stdio.h>
#include <string.h>


void delete( char string[], char substr[] ) {

	int i = 0 ;

	int stringlength = strlen(string);
	int substrlength = strlen(substr);


	while ( i < stringlength ) {

		if (strstr(&string[i], substr) == &string[i]) {

		/*
			shift up string by length of substr 
		*/

			stringlength -= substrlength;

			for (int j=i; j < stringlength; j++) 
				string[j] = string[j+substrlength];
				/* could use memcpy() */
		} else i++;

	}
	string[i] = '\0';

}

int main () {

	char string[] = "the cat chased the mouse";

	delete(string, "the ");

	printf("%s\n", string);

	return 0;
}
