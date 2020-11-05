#include <ncurses.h>

#include "Task.h"
#include "Project.h"

showProjectScreen()
{
	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);

	WINDOW win = newwin(max_y/2, max_x - 2, 1, 1);
	refresh();
	box(win, 0, 0);
	wprintw(win,"Projetos");
	showProjects(win);
	wrefresh(win);

}

int main()
{
	// inicializa a tela
	// prepara o buffer de memoria limpa a tela
	initscr();
	cbreak();
	noecho();
	start_color();

	refresh();

	getch();

	// desaloca a memoria e termina ncurses
	endwin();
	return 0;
}
