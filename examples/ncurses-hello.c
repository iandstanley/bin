
                  /* NCURSES Hello World in C */


#include <ncurses.h>


int main() {

	initscr();

	start_color();

	init_pair(1, COLOR_RED, COLOR_BLACK);

	attron(COLOR_PAIR(1));

	printw("Hello World!");

	attroff(COLOR_PAIR(1));

	refresh();

	getch();

	endwin();

	return 0;

}

/*

	$ cc ncursaes-hello.c -lncurses

*/

