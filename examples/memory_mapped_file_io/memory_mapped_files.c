#include	<sys/types.h>
#include	<fcntl.h>
#include	<sys/mman.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<sys/stat.h>
#include	<unistd.h>


int main(int argc, char ** argv) {

	// mmap can be used to map files into memory!

	int fd = open("./sometext.txt", O_RDONLY, S_IRUSR | S_IWUSR);

	struct stat sb;

	if (fstat(fd, &sb) == -1) {
		perror("couldn't get file size\n");
	}
	printf("file size is %ld\n", sb.st_size);


	char *file_in_memory = mmap(NULL,sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

	/*
	 * 	We can change the file in memory and have it automatically written
	 * 	back to the file. In order to do so, we should change the above C
	 * 	statementfrom PROT_READ to PROT_READ | PROT_WRITE. We will also
	 * 	need to open the file for O_RDWR (read/write), and we need to change
	 * 	our MAP_PRIVATE to MAP_SHARED (without this last changeany changes
	 * 	made in memory may not be written back to the file.
	 * 
	 * 	Now we could just have manipulation statements instead of the printf
	 * 	e.g.
	 * 
	 * 		#include	<xlocale.h>
	 * 
	 * 		if (( i % 2) == 0) {
	 * 			file_in_memory[i] toupper(file_in_memory[i]);
	 * 		} 	// change every other letter to uppercase
	 * 	
	 */

	printf("Printing file, as an array of chars\n");

	for (int i = 0 ; i < sb.st_size ; i++) {
		printf("%c", file_in_memory[i]);
	}

	printf("\n"); 	// or other method for flushing buffered text etc

	munmap(file_in_memory, sb.st_size);
	close(fd);
}
