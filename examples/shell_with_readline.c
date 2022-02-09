/*
	Writing a custom shell or cli with readline library in C
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>


unsigned char command_buf;

void main() {

	while (1) {
	
		command_buf = readline("prompt> ");

		if (strlen(command_buf) > 0) add_history(command_buf);

		if (!strcmp(command_buf, "ifconfig")) {
			system("ifconfig"); }
		else if (!strcmp(command_buf, "date")) {
			system("date"); }
		else if (!strcmp(command_buf, "exit")) {
			break; }

	}
	
	return 0;
}

