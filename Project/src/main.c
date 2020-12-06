#include <ncurses.h>
#include "Display.h"


void init();
void end();
int run(int *status);


int main(){
    int status;
	run(&status);	
	return 0;
}


void init(){

	initscr();
	noecho();
	cbreak();
	curs_set(0);

	start_color();
    initColors();
}


void end(){
	endwin();
}


int run(int *status)
{

	init();
    bool exit = FALSE;

    int main_menu_option = mainMenu(status);

    while (!exit)
    {
        switch (main_menu_option)
        {
        case 2:
            exit = TRUE;
            break;
        case 4:
            exit = TRUE;
            break;
        default:
            exit = TRUE;
        }
    }

	end();
    return OK;
}

