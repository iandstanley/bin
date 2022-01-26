/* string append (concat) with dynamic memory alloc  */

#include	<stdio.h>
#include 	<string.h>
#include	<stdlib.h>


char * string_append(char * s1, char * s2);	// allocates space on HEAP for both strings


int main(void) {

	char first[20] = "first ";
	char second[20] = "second";

	char * s = string_append(first, second);

	printf("%s\n", s);

	free (s);
}

char * string_append(char *s1, char *s2) {

	int s1_length = strlen(s1); 
	int s2_length = strlen(s2); 
	int size = s1_length + s2_length +1;

	char * s = calloc(size, sizeof(char));

	for (int i=0 ; i < s1_length ; i++)
		s[i] = s1[i];

	for (int i=0 ; i < s2_length ; i++)
		s[s1_length + i] = s2[i];

	s[size-1] = '\0';

	return s;
}


/*

NB strtok has some problems.

	(i) 	neads 2+ calls
	(ii)    strtok is NOT THREAD SAFE as it uses static local
	variables which could cause crashes / memory corruption
	etc.


Here you have TWO options: strtok_r() or strsep():

	char str[] = "This is a test";
	char * token;
	char * rest;

	rest = str;

	while (( token = strtok_r(rest, " ", &rest) )) {
		printf("token = %s\n", token);
	}


	/************************************************/

	char str[] = "This is a test";
	char * token;

	while (( token = strsep(&str, " ") != NULL ) {
		printf("token %s\n", token);
	}

	/************************************************/

NOTES:

	(i)     all 3 functions are DESTRUCTIVE! so can't be used
	with constants -- use strdup() to duplicat on heap.

	(ii)    strtok() and strtok_r() are part of ANSI C. strsep90
	is included in both GNu Standard Library and also CLANG Std
	Library (eg FreeBSD) but can be a little less portable.

	(iii)   strtok_r() and strsep() allow you to set multiple
	delimiters.

	(iiii)  strtok_r() and strtok() will ignore multiple repeating
	delimeters but strsep() will return empty delimieted tokens.



