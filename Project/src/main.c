#include <ncurses.h>
#include "Display.h"


void init();

void end();

int run(int *status);


int main(){

	init();
	run(&status);	
	end();

	return 0;
}


void end(){
	endwin();
}


void init(){

	initscr();
	noecho();
	cbreak();
	curs_set(0);

	start_color();
	init_colors();
}


int run(int *status)
{
    bool exit = FALSE;

    int main_menu_option = main_menu(status);

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

    return OK;
}

