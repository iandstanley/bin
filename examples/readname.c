/*
	readname.c

	Simple program to rad text from panel input

	Language:	C
	Libraries:	XView, OpenLook, X-Windows
*/


#define	MYWIDTH		300
#define	MYHEIGHT	100

#include	<xview/xview.h>
#include	<xview/panel.h>
#include	<xview/notice.h>


Frame		frame;
Panel		panel;
Panel-item	label;
Panel-item	input;

char *ips, ops[60];


void ok() {
	ips = (char *) xv_get(input, PANEL_VALUE);
	sprintf(ops, "Hello - %s.", ips);
	xv_set(label, PANEL_LABEL_STRING, ops, NULL);
}


void bye() {
	sprintf(ops, "Bye %s.", ips);
	notice_prompt(panel, NULL, NOTICE_MESSAGE_STRINGS, 
		ops, NULL, NULL);
	exit(0);
}



void main(argc, argv)
int argc;
char * argv[];
{

	xv_init(XV_INIT, ARGC_PTR_ARGV, &argc, argv, NULL);

	frame = (Frame) xv_create(XV_NULL, FRAME,
		FRAME_LABEL, argv[0], 
		XV_WIDTH, MYWIDTH, 
		XV_HEIGHT, MYHEIGHT, NULL);

	panel = (Panel) xv_create(frame, PANEL,
		XV_WIDTH, MYWIDTH, 
		XV_HEIGHT, MYHEIGHT, NULL);

	input = (Panel_item) xv_create(panel, PANEL_TEXT, 
		PANEL_LABEL_STRING, 
		"Please enter your name: ", NULL);

	(void) xv_create(panel, PANEL_BUTTON, 
		PANEL_LABEL_STRING, "OK", 
		PANEL_LABEL_PROC, ok, NULL);

	label = (Panel_item) xv_create(panel, 
		PANEL_MESSAGE, 
		PANEL_LABEL_STRING, "Welcome", NULL);

	(void) xv_create(panel, PANEL_BUTTON, 
		PANEL_LABEL_STRING, "BYE", 
		PANEL_ITEM_X, 260
		PANEL_ITEM_Y, 50,
		PANEL_NOTIFY_PROC, bye, NULL);

	window_fit(frame);

	window_main_loop(frame);
}



/*

	$ gcc readname.c -o readname -lxview -lolgx -lx11 \
		-I/usr/X11R6/include -I/usr/X11R6/include/X11 \
		-L/usr/X11R6/xview -L/usr/X11R6/lib


*/


