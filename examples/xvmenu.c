/*
	xvmenu.c

	Simple button with menu

	Language: 	C
	Libraries:	XView, Openlook, X-Windows
*/


#include 	<xview/xview.h>
#include 	<xview/panel.h>
#include 	<xview/openmenu.h>


Frame	frame;
Panel	panel;
Menu	menu1;


void menu1_proc(menu, menu_item)
Menu menu; 
Menu_item menu_item;
{
	char* menuchoice = (char *)xv_get(menu_item, MENU_STRING);

	puts(menuchoice);

	if (strcmp(menu_choice, "Quit") == 0) {
		puts("Thanks");
		exit(0);
	}
}


main(argc, argv) 
int argc;
char *argv[];
{

	xv_init(XV_INIT_ARGC_PTR_ARGV, &argc, argv, NULL);

	frame = (Frame) xv_create(frame, PANEL,
		XV_WIDTH, 300, XV_HEIGHT, 200, NULL);

	menu1 = (Menu) xv_create(0, MENU,
		MENU_TITLE_ITEM, "Continents",
		MENU_STRINGS, 
			"Africa", "Asia", "Europe", 
			"N.America", "S.America", 
			"Quit", NULL,
		MENU_NOTIFY_PROC, menu1_proc, NULL);

	(void) xv_create(panel, PANEL_BUTTON,
		PANEL_LABEL_STRING, "Hello",
		PANEL_ITEM_MENU, menu1, NULL);

	window_fit(frame);
	window_main_loop(frame);
}



/*

	$ gcc  xvmenu.c -o xvmenu -lxview -lolgx -lX11 \
		-I/usr/X11R6/include/X11 \
		-L/usr/X11R6/lib/xview -L/usr/X11R6/lib

*/



