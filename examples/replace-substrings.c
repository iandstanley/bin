
	/* REPLACE ALL OCCURANCES OF A SUBSTRING WITH ANOTHER STRING */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char * replace( char* before, char* oldsub, char* newsub){

	int oldlen = strlen(oldsub);
	int newlen = strlen(newsub);
	int beforelen = strlen(before);

	char* after;

	if (oldlen == newlen) {

		after = malloc((beforelen+1) * sizeof(char));

	} else {

	/* loop trough before string and calc occurances */

		int occurances = 0;
		int i=0;

		while (i < beforelen) {

			if (strstr(&before[i], oldsub) == &before[i]) {
				occurances++;
				i += oldlen;	// shift ahead
			} else i++;
		}

		int subdiff = newlen - oldlen;
		int afterlen = beforelen;

		afterlen += occurances * subdiff;

		after = malloc((afterlen+1) * sizeof(char));

		int j = 0;
		i = 0;

		while (i < strlen(before)) {

			if (strstr(&before[i], oldsub) == &before[i]) {
				strcpy(&after[j], newsub);

				i += oldlen;
				j += newlen;

			} else {
				after[j] = before[i];

				i++;
				j++;
			}



		}

		after[j] = '\0';
	}

	return after;
}


int main () {

	char string[] = "the cat chased the mouse";

	char * result = replace(string, "the ", "a ");

	printf("Before = %s\n", string);

	printf("After = %s\n", result);

	free(result);

	return 0;
}
