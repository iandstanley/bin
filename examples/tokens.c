#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



char * tokenize(char * url) {

	char * path; 

	printf("tokenize(%s)\n", url);	

	strtok(url, "/"); 	// get rid of 'gopher:'

	strtok(NULL , "/");	// get rid of '<hostname>/'

	path = strtok(NULL , "/");
	
	return path;
}


int main() {

	char myurl[] = "gopher://localhost/gophermap";
	char * mypath;

	mypath = tokenize(myurl);

	printf("Path = %s\n", mypath);

}
