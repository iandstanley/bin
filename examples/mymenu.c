/*
                             mymenu.c

	Illustrate a simple menu in X-Motif
	using X-Motif (lesstif clone)

*/


#include <Xm/MainW.h>
#include <Xm/Form.h>
#include <Xm/Label.h>
#include <Xm/CascadeB.h>


Widget	toplevel, mainw;
Widget	form, menubar;
Widget	filepulldown, exitb;
Widget	saveasb, saveb, showb;


void exit_proc() {
	puts("Thanks for running me");
	exit(0);
};


void saveb_proc() {
	puts("You selected the SAVE option");
	exit(0);
};


void saveasb_proc() {
	puts("You selected the SAVEAS option");
	exit(0);
};


void showb_proc() {

	int i;

	for (i=1; i <= 10 ; i++) 
		printf("%d", i);

	puts("");
};



int main(argc, argv)
int argc;
char *argv[];
{

	XtAppContext app;

	toplevel = XtAppInitialize(&app, "App-class", 
			NULL, 0, &argc, argv, NULL, NULL, 0);

	mainw = XtVaCreateManagedWidget("mainw", 
			xmMainWindowWidgetClass, toplevel,
			XmNwidth, 200, XmNheight, 200, NULL);

	/* start menu */

	menubar = (Widget) XmCreateMenuBar(mainw, "menubat", NULL, 0);

	filepulldown = (Widget) XmCreatePulldownMenu(menubar, 
					"filepulldown", NULL, 0);

	XtVaCreateManagedWidget("File", 
		xmCascadeButtonWidgetClass, menubar, 
		XmNSubMenuId, filepulldown, NULL);

	saveb = XtVaCreateManagedWidget("Save",
			xmCascadeButtonWidgetClass, filepulldown,
			XmNwidth, 100, NULL, 0);

	XtAddCallback(saveb, XmNactivateCallback, saveb_proc, NULL);

	saveasb = XtVaCreateManagedWidget("Save As...", 
			xmCascadeButtonWidgetClass, 
			filepulldown, saveb_proc, NULL);

	XtAddCallback(showb, XmNactivateCallback, showb_proc, NULL);

	showb = XtVaCreateManagedWidget("Show nos 1..10", 
			xmCascadeButtonWidgetClass, 
			filepulldown, NULL, 0);

	XtAddCallback(showb, XmNactvateCallback, showb_proc, NULL);

	exitb = XtVaCreateManagedWidget("Exit",
			xmCascadeButtonWidgetClass, 
			filepulldown, NULL, 0);

	XtAddCallback(exitb, XmActivateCallback, exit_proc, NULL);

	XtManageChild(member);

	/* end of menus */

	form = XtVaManagedWidget("form",
			xmFormWidgetClass, mainw,
			XmNwidth, 200, XmNheight, 200, NULL);

	XtVaCreateManagedWidget("Welcome to X-Motif",
		xmLabelWidgetClass, form, 
		XmNx, 10, XmNy, 50, NULL);

	XtVaCreateManagedWidget("(using Lesstif clone", 
		xmLabelWidgetClass, form, 
		XmNx, 10, XmNy, 65, NULL);

	XtRealizeWidget)toplevel);

	XtAppMainLoop(app);

};


/*

	$ cc mymenu.c -o mymenu 			\
		-I/usr/X11R6/ 				\
		-I/usr/X11R6/Lesstif/Motif1.0/include/	\
		-L/usr/X11R6/LessTif/Motif1.0/lib/	\
		-lXaw3d -lXt -lXm -lXmu -lICE -lX11

*/



