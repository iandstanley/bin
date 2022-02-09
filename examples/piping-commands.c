#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/wait.h>
#include	<unistd.h>

/*
	example program emulating the shell command

	$ ping -c 5 google.com | grep avg

	Original example written on Linux  grep'ped for rtt 
	However, FreeBSD prints round-trip instead of rtt
*/

int main() {

	int fd[2];

	if ( pipe(fd) == -1 ) {
		return 1; 
	}

	int pid1 = fork();
	if (pid1 < 0) {
		return 2;
	}

	if (pid1 == 0) {

	/*
		Child process #1 (ping)

		* We need to duplicate STDOUT of parent process
		* We close fd[0] because we don't use it
		* We close fd[1] as it remains open even though we
		  duplicated it. dup2() doesn't reassign the fd, 
		  it creates another one matching the supplied fd.

		NB fd[1] is the right end of the pipe
	*/

		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);

		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}

	// parent continues ... 

	int pid2 = fork();
	if (pid2 < 0) {
		return 3;
	}

	if (pid2 == 0) {
	/*
		Child process #2 (grep)

		Got to do the same thing again with the fd's
		but this time with STDIN, fd[0 the reading end
		of the pipe.
	*/

		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);

		execlp("grep", "grep", "avg", NULL);
	}

	// close the fd's of the parent process on the pipe
	close(fd[0]);
	close(fd[1]);

	waitpid(pid1, NULL, 0);	
	waitpid(pid2, NULL, 0);	

	return 0;
}

