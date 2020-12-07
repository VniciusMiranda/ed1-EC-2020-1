#include "Display.h"
#include "Project.h"

void createProjectScreen()
{
    // Clear the screen
    clear();
    refresh();

    // Gets the height and width
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // Create the top window
    WINDOW* top_win = newwin(max_y / 2 - 2, max_x - 2, 1, 1);
    refresh();
    box(top_win, 0, 0);
    wprintw(top_win, "Novo Projeto");
    wrefresh(top_win);

    // Create the bottom window
    WINDOW* bot_win = newwin(max_y / 2 - 2, max_x - 2, max_y / 2 + 1, 1);
    refresh();
    box(bot_win, 0, 0);
    wprintw(bot_win, "Crie seu Projeto");
    wrefresh(bot_win);

    // Input Windows

    // Inputs
    int exit = FALSE, title_width;
    char *question;
    char title[TITLE_SIZE];
    char description[DESCRIPTION_SIZE];
    while(!exit){
        echo();
        question = "Digite o nome do projeto:";
        title_width = strlen(question);
        mvwprintw(bot_win, 4, 4, "%s", question);
        wrefresh(bot_win);
        mvwscanw(bot_win, 4, 6 + title_width, "%s", &title);
        wrefresh(bot_win);
        question = "Digite a descrição do Projeto:";
        title_width = strlen(question);
        mvwprintw(bot_win, 8, 4, "%s", question);
        wrefresh(bot_win);
        mvwscanw(bot_win, 8, 6 + title_width, "%s", &description);
        wrefresh(bot_win);

        int c = wgetch(bot_win);
        if(c == 't'){
            noecho();
            clear();
            refresh();
            exit = TRUE;
            break;
        }
    }

}

void showProjectScreen()
{
    // Clear the screen
    clear();
    refresh();

    // Gets the height and width
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // Create the top window
    WINDOW* top_win = newwin(max_y / 2 - 2, max_x - 2, 1, 1);
    refresh();
    box(top_win, 0, 0);
    wprintw(top_win, "Projetos");
    int process = showProjects(top_win);
    wrefresh(top_win);

    // Create the half-screen windows
    WINDOW* botL_win = newwin((max_y / 2 - 2), (max_x / 2) - 1, (max_y / 2) + 1, 1);
    refresh();
    box(botL_win, 0, 0);
    wrefresh(botL_win);

    WINDOW* botR_win = newwin((max_y / 2 - 2), (max_x / 2) - 1, (max_y / 2) + 1, (max_x / 2) + 1);
    refresh();
    box(botR_win, 0, 0);
    wrefresh(botR_win);

    char *options[] = { "Voltar" };

    char *question;
    int num_options;
    int title_width;
    int choice;
    int nProjects = getNumbProjects();

    if (process == -1)
    {
        // creating select menu
        question = "Não existem projetos";
        num_options = sizeof(options) / sizeof(char *);
        title_width = (strlen(question) + 10)/2;
        choice = selectWin(options, question, num_options, max_y * 5 / 8, max_x / 4 - title_width, 0, 0, 0);

        bool exit = FALSE;

        while (!exit)
        {
            switch (choice)
            {
            case 0:
                clear();
                refresh();
                exit = TRUE;
                break;
            default:
                clear();
                refresh();
                exit = TRUE;
            }
        }
    }
    else
    {
        // creating select menu
        for (int i = 0; i < nProjects; i++)
        {
            options[i] = strcat("Projeto ", (char)(i + 1));
        }
        question = "Selecione um projeto:";
        num_options = sizeof(options) / sizeof(char *);
        title_width = (strlen(question) + 10)/2;
        choice = selectWin(options, question, num_options, max_y * 5 / 8, max_x / 4 - title_width, 0, 0, 0);
    }
}