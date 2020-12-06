#include "Display.h"


int projectScreen()
{
    // Clear the screen
    clear();
    refresh();

    // Gets the height and width
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // Create the top window
    WINDOW* top_win = newwin((max_y / 2 - 2), max_x - 2, 1, 1);
    refresh();
    box(top_win, 0, 0);
    wprintw(top_win, "Projetos");
    int process = showProjects(top_win);
    wrefresh(top_win);

    // Create the bottom window
    WINDOW* bot_win = newwin((max_y / 2 - 2), max_x - 2, (max_y / 2) + 1, 1);
    refresh();
    box(bot_win, 0, 0);
    wrefresh(bot_win);

    // Create the half-screen windows
    WINDOW* botL_win = newwin((max_y / 2 - 2), (max_x / 2) - 1, (max_y / 2) + 1, 1);
    refresh();
    box(botL_win, 0, 0);
    wrefresh(botL_win);

    WINDOW* botR_win = newwin((max_y / 2 - 2), (max_x - 2) - 1, (max_y / 2) + 1, max_x / 2);
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
        question = "Não existem projetos.";
        num_options = sizeof(options) / sizeof(char *);
        title_width = (strlen(question) + 10)/2;
        choice = selectWin(options, question, num_options, max_y * 5 / 8, max_x / 4 - title_width, 0, 0, 0);
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


    return OK;
}