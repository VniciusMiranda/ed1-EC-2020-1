#include "Display.h"
#include "Task.h"

int main_menu(int *err){

	int max_y, max_x;

	getmaxyx(stdscr, max_y, max_x);


    // banner thread setup
    PrintBannerArgs args;
	bool stop = FALSE;

    args.stop = &stop;
    args.x = max_x/2 - 40;
    args.y = 0;

    pthread_create(&banner_th, NULL, printBanner, &args);

    // there is a bug that breaks the other components if this is not called :/
    usleep(3000);

    // creating select menu
	char* options[] = {
		"Criar um Projeto",
		"Carregar Projeto",
        "Ver Projetos",
        "Ajuda",
		"sair :c"
	};


	char* question = "Bem-Vindo ao Project Organizer";
	int num_options = sizeof(options)/sizeof(char*);

    int choice = selectWin(options, question, num_options, 25, max_x/2 - 25, 0, 0, 0);

	stop = TRUE;

    pthread_join(banner_th, NULL);


    return choice;
}