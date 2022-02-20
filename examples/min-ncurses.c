
                   /* A minimal ncurses app  */


#include <ncurses.h>

int main() {

	initscr();

	start_color();

	WINDOW* win;

	/* height, width, y, x */
	win = newwin(10,10,10,10);

	wrefresh(win);

	delwin(win);

	refresh();

	getch();

	endwin();

	return 0;
}


