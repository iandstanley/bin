/*
 * 
 * Sample <sys/queue.h> application
 * 
 */


#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/queue.h>


typedef struct _Cat {
	// equivalent of:   struct _Cat *next;
	LIST_ENTRY(_Cat) pointers;

	char name[255];
	int color;
	char can_climb;
} Cat;


Cat * create_cat(char *name, int color, char can_climb);

LIST_HEAD(cat_list, _Cat) cats;

int main() {

	Cat * cat1 = create_cat("Cat1", 2, 0);
	Cat * cat2 = create_cat("Cat2", 3, 1);
	Cat * cat3 = create_cat("Cat3", 4, 0);
	Cat * cat4 = create_cat("Cat4", 2, 0);

	LIST_INIT(&cats);

	LIST_INSERT_HEAD(&cats, cat1, pointers);
	LIST_INSERT_HEAD(&cats, cat2, pointers);
	LIST_INSERT_AFTER(cat2, cat3, pointers);
	LIST_INSERT_AFTER(cat3, cat4, pointers);

	LIST_REMOVE(cat4, pointers);

	Cat *cat;

	LIST_FOREACH(cat, &cats, pointers) {
		printf("%s\n", cat->name);
	}
}

Cat *create_cat(char *name, int color, char can_climb) {

	Cat *cat = (Cat *)malloc( sizeof(Cat) );

	strcpy(cat->name, name);

	cat->color = color;

	cat->can_climb = can_climb;

	return cat;
}


