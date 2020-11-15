#include <ncurses.h>
#include "Display.h"

#define DEBUG TRUE

// n curses config and project init functions
void init(){

	initscr();
	noecho();
	cbreak();
	curs_set(0);

	start_color();
	init_colors();
}


int main(){

	init();


	int status;
	int  location = projectOrganizer(&status);	

	endwin();

	if(status != OK)
	{
		printf("an error has occured.\n");
		printf("status code: %d\n", status);
		printf("location: %d\n", location);
		printf(":/\n");
		return -1;
	}
	else if(DEBUG)
	{
		printf("status code: %d\n", status);
		printf("location: %d\n", location);
		printf(":/\n");
	}

	printf("bye :)\n");


	return 0;
}
