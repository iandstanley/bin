#include <stdio.h>
#include <string.h>

int main () {

	char url[] = "gopher://localhost:7070/folder/gophermap";
	char * ptr;

	ptr = strtok(url, "/");
	printf("token = %s\n", ptr);
	printf("url = %s\n", url);

	ptr = strtok(NULL, "/");
	printf("token = %s\n", ptr);
	printf("url = %s\n", url);

	ptr = strtok(NULL, "\0");
	printf("token = %s\n", ptr);
	printf("url = %s\n", url);

	ptr = strtok(NULL, "/");
	printf("token = %s\n", ptr);
	printf("url = %s\n", url);

	char str[] = "This works!Great";
	char sep[] = " !";

	ptr = strtok(str, sep);
	printf("str token = %s\n", ptr);

	ptr = strtok(NULL, sep);
	printf("str token = %s\n", ptr);

	ptr = strtok(NULL, sep);
	printf("str token = %s\n", ptr);

}


	/*

	$ cc strtok.c
	
	$ ./a.out
	
	Name
	Age
	RolNo
	Marks

	$



	You can also tokenize with multiple separators.

		char sep[] = " !";
		char str[] = "This works!Great"
		char *ptr;

		ptr = strtok(str, sep);		// This
		ptr = strtok(NULL, sep);	// works
		ptr = strtok(NULL, sep);	// Great

	*/
