/*
	days-christmas.c , an X program

	Calculate how many days to Christmas
	Uses: X-Windows / X-Motif toolkit
*/


#include <Xm/List.h>
#include <Xm/Form.h>
#include <Xm/MainW.h>
#include <Xm/PushB.h>
#include <Xm/Label.h>
#include <stdio.h>


#define	NOV	11
#define	DEC	12
#define XDAY	25
#define	YDAYS	365
#define MYNULL	'\0'


void exit();

string	myfont[] = {
	"*.renderTable:  TAG",
	"*.fontType: FONT_IS_FONT",
	"*.TAG.fontName: -*-courier-bold-r-*--*-240-*",
	NULL
};

char *months[] = {
	"January", "February", "March",
	"April", "May", "June", 
	"July", "August", "September",
	"October", "November", "December"
};

int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};

int	month_no;

Widget	dia;
Widget	toplevel, listw;
Widget	myform, mymainw;
Widget	mydate;
Widget	exitb;


void	sel_callback(listw, clientdata, calldata)
Widget listw;
XtPointer clientdata;
XtPointer calldata;
{

	int i, x, y;
	static char tag[30][5];

	XmListCallbackStruct *cbs = (XmListCallbackStruct *) calldata;
	char *choice;

	Widget myform2;

	XmStringGetLtoR(cbs->item, XmFONTLIST_DEFAULT_TAG, &choice);

	printf("Selected item: %s (%d)\n", choice, cbs->item_position);
	month_no = cbs->items_position;

	XtFree(choice);

	dia = (Widget) XmCreateTemplateDialog(listw, 
			months[month_no-1], NULL, 0);
	
	myform2 = XtVaCreateManagedWidget( "myform", 
			xmFormWidgetClass, dia, 
			XtNwidth, 300, XtNheight, 200, NULL);

	/* make array of buttons for selected month. one per day */

	for (i=1, x=5, y=5; i <= days[month_no-1]; i++) {
		sprintf(tag[i], "%d", i);
		x += 40;
		if (x>250) {
			x = 5; 
			y += 40;	// new row
		}

		mydate = XtVaCreateManagedWidget(tag[i], 
			xmPushButtonWidgetClass, myform2,
			XtNx, x, XtNy, y, 
			XtNwidth, 40, XtNheight, 40, NULL);

		XtAddCallback(mydate, XmNactivateCallback, run, tag[i]);
	}

	x = 20;
	y = 20;

	XtManageChild(dia);
	XtRealizeWidget(dia);

}


void	run(wid, clientdata, calldata) 
Widget 		wid;
XtPointer	clientdata;
XtPointer	calldata;
{
	char	text[2], op[50];
	int	dd, d2x, i;
	Widget	mess;

	strcpy(text, (char *) clientdata);
	puts(text);
	sscanf)text, "%d", &dd);

	/*
		if Deceber count upto 25th;
		if after 25th add 365 to count to Christmas next
		year
	*/

	if (month_no == DEC) {
		d2x = XDAY -dd;
		if (d2x < 0) d2x =+ DAYS;
	} else {

	/*
		if not Decemberm get to end of current month, 
		add days for months upto December, 
		then add 25 to Christmas day
	*/

		d2x = days[month_no-1] - dd;

		for (i = month_no + 1; i < DEC ; i++)
			d2x =+ days[i-1];

		d2x =+ XDAY;
	}

	printf("%d days to Christmas\n", d2x);
	sprintf(op, "%d days to Christmas\n", d2x);

	mess = (Widget) XmCreateInformationDialog( listw, "Days",
				NULL, 0);

	XtVaSetValues(mess, XmNmessageString, 
		XmStringCreateLocalized(op), NULL);

	XtManageChild(mess);

	XtPopup(XtParent(mess), XtGrabNone);
};


void 	tab(n)
int n;
{

	for ( ; n > 0 ; --n)
		putchar(' ');
};


void substr(s, n, m, sl)
char *s, *sl;
int n, m;
{
	int i;
	for (i=0 ; i<m ; ++i)
		*sl++ = *(s+i+n);
	*sl = NY_NULL;
};


void	myexit()
{
	char *thanks = "Thanks trying this";
	char tmp[20];
	int i;

	for (i=0 ; i < 11 ; i++) {
		tab(10 - i);
		substr(thanks, 10 - i, 2 * i, tmp);
		puts(tmp);
	};

	puts("        BYE");
	exit 0;
};


int main(argc, argv)
int argc;
char *argv[];
{

	XtAppContext	app;

	int i, n = XtNumber(months);
	XmStringTable str_list;
	int nlines;

	XtSetLanguageProc(NULL, NULL, NULL);

	toplevel = XtVaAppInitialize(&app, "Demos", NULL, 0,
			&argc, argv, myfont, NULL);

	mymainw = XtVaManagedWidget("mymainw", 
			xmMainWindowWidgetClass, toplevel, 
			XtNwidth, 500, XtNheight, 450, NULL);	

	myform = XtVaCreateManagedWidget("myform", 
			xmFormWidgetClass, mymainw, 
			XtNwidth, 500, XtNheight, 450, NULL);

	XtVaCreateManagedWidget("Please Select\nMonth",
			xmLabelWidgetClass, myform, 
			XtNx, 250, XtNy, 20, NULL);

	exitb = XtVaCreateManagedWidget("EXIT",
			xmPushButtonWidgetClass, myform,
			XtNx, 220, XyNy, 400, 
			XtNwidth, 150, XtNheight, 30, NULL);

	str_list = (XmStringTable) XtMalloc(n * sizeof(XmString*));

	nlines = DEC;

	for (i=0; i < nlinesl i++)
		str_list[i] = XmStringCreateLocalized(months[i]);


	listw = XmCreateScrolledList(myform, "months", NULL, 0);

	XmVaSetValues(listw, 
		XmNvisibleItemCount, nlines, 
		XmNitemCount, nlines,
		XmNitems, str_list, 
		XmNx, 50, XmNy, 50, 
		XmNwidth, 50, XmNheight, 50, NULL);


	XtAddCallback(listw, XmNbrowseSelectedCallback,
		sel_callback, NULL);


	XtAddCallback(exitb, XmActivateCallback, myexit, NULL);

	XtManageChild(listw);
	XtRealizeWidget(toplevel);
	XtAppMainLoop(app);
}


/*
	$ cc days-christmas.c -o cdays		\
		-I/usr/include/X11 		\
		-I/usr/include/Xm		\
		-L/usr/X11R6/			\
		-lXm -lXt -lX11

*/


