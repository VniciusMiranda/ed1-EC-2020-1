#include "Display.h"
#include "Project.h"

void init_colors()
{
    for (int i = 0; i < NUMB_COLORS; i++)
        INIT_PAIRS[i] = FALSE;
}

void *printBanner(void *args)
{

    char *banner_lines[] = {

        "8888888b.                   d8b                   888   ",
        "888   Y88b                  Y8P                   888   ",
        "888    888                                        888   ",
        "888   d88P 888d888 .d88b.  8888  .d88b.   .d8888b 888888",
        "8888888P`  888P`  d88``88b `888 d8P  Y8b d88P`    888   ",
        "888        888    888  888  888 88888888 888      888   ",
        "888        888    Y88..88P  888 Y8b.     Y88b.    Y88b. ",
        "888        888     `Y88P`   888  `Y8888   `Y8888P  `Y888",
        "                            888                         ",
        "                           d88P                         ",
        "                         888P                           ",

        " .d88888b.                                    d8b                           ",
        "d88P` `Y88b                                   Y8P                           ",
        "888     888                                                                 ",
        "888     888 888d888 .d88b.   8888b.  88888b.  888 88888888  .d88b.  888d888 ",
        "888     888 888P`  d88P`88b     `88b 888 `88b 888    d88P  d8P  Y8b 888P`   ",
        "888     888 888    888  888 .d888888 888  888 888   d88P   88888888 888     ",
        "Y88b. .d88P 888    Y88b 888 888  888 888  888 888  d88P    Y8b.     888     ",
        " `Y88888P`  888     `Y88888 `Y888888 888  888 888 88888888  `Y8888  888     ",
        "                         888                                                ",
        "                    Y8b d88P                                                ",
        "                     `Y88P`                                                 "

    };

    int banner_size = sizeof(banner_lines) / sizeof(char *);
    int banner_width = strlen(banner_lines[11]);
    int banner_height = banner_size;

    PrintBannerArgs *pb = (PrintBannerArgs *)args;

    bool *stop = pb->stop;
    int y = pb->y, x = pb->x;

    int begin_y = y;

    int color_id, start_color = COLOR_BLUE;

    int start_color_id = start_color + 8, color_update = start_color_id;
    int max_color_id = 16;

    // the pairs will be init with  8 =< ID < 16
    // so that it doesn't conflit with the pairs used on labels
    for (int i = start_color; i < 8; i++)
        init_pair(i + 8, i, COLOR_BLACK);

    while (TRUE)
    {

        if (*stop)
            break;

        noecho();
        color_id = color_update;
        y = begin_y;

        for (int i = 0; i < banner_size; i++)
        {
            attron(COLOR_PAIR(color_id));
            mvprintw(y++, x, "%s", banner_lines[i]);
            attroff(COLOR_PAIR(color_id));

            color_id = color_id < max_color_id ? color_id + 1 : start_color_id;
        }

        color_update = color_update < max_color_id ? color_update + 1 : start_color_id;
        usleep(100000);
        refresh();
    }
}


int eraseWin(WINDOW* w, int height, int width){
    if(!w)
        return ERR;

    // erase what's inside the window
    for(int i = 0; i < height; i ++)

        for( int j = 0; j < width; j++)
            mvwprintw(w, i, j, " ");

     wrefresh(w); 
    delwin(w);


    return OK;
}




int selectWin(char** options, char* question, int num_options, int y, int x, unsigned int width, unsigned int height,  int default_choice){

    int select_width;
    int select_height;

    if (!width || !height)
    {
        select_width = strlen(question) + 10;
        select_height = num_options + 4;
    }
    else
    {
        select_width = width;
        select_height = height;
    }

    // define the location considering the size of the win
    int select_x = x;
    int select_y = y;

    select_x = select_x < 0 ? 0 : select_x;
    select_y = select_y < 0 ? 0 : select_y;

    WINDOW *select_win = newwin(select_height, select_width, select_y, select_x);

    box(select_win, 0, 0);

    int question_length = strlen(question);

    int select_middle_x = select_width / (2 * DIS_CONV_FACTOR);
    int select_middle_y = select_height / (2 * DIS_CONV_FACTOR);

    mvwprintw(select_win, 0, select_middle_x, question);

    keypad(select_win, TRUE);

    refresh();

    bool exit = FALSE;

    int selected_option = default_choice;

    while (!exit)
    {
        // print the options
        for(int i = 0; i < num_options; i++)
        {
            if (i == selected_option)
                wattron(select_win, A_REVERSE);

            mvwprintw(select_win, 2 + i, select_middle_x, options[i]);
            wattroff(select_win, A_REVERSE);
        } 
        wrefresh(select_win);
        
        int key = wgetch(select_win);
        
        // manage key input 
        switch(key)
        {
        case KEY_UP: // key up
            selected_option--;
            break;
        case KEY_DOWN: // key down
            selected_option++;
            break;
        case 10: // enter
            exit = TRUE;
            break;
        }

        if (selected_option < 0)
            selected_option = num_options - 1;

        if (selected_option > num_options - 1)
            selected_option = 0;

        wrefresh(select_win);
    }

    delwin(select_win);

    refresh();
    return selected_option;
}

int inputWin( char* question, int y, int x, unsigned int width, unsigned int height, char* answer){

    if(!answer) return ERR;


    echo();
    curs_set(1);

    WINDOW *input_win = newwin(width, height, y, x);
    if (!input_win)
        return ERR;

    // conversion of scr_width to char_length
    width *= DIS_CONV_FACTOR;

    char str[width];

    box(input_win, 0, 0);

    wattron(input_win, A_REVERSE);
    mvwprintw(input_win, 0, (width - strlen(question)) / 2, "%s", question);
    wattroff(input_win, A_REVERSE);

    refresh();
    wrefresh(input_win);

    keypad(input_win, TRUE);

    char c;
    int i = 0;

    wmove(input_win, 1, 1);

    while (c != 10 && i < width)
    {
        c = wgetch(input_win);
        str[i++] = c;
    }

    delwin(input_win);

    noecho();
    curs_set(0);

    strcpy(answer, str);

    return OK;
}

// main display loop
int loop(int *status)
{
    bool exit = FALSE;
    int main_menu_option;
    while (!exit)
    {
        main_menu_option = main_menu(status);
        switch (main_menu_option)
        {
        case 0:
            createProjectScreen();
            continue;
        case 2:
            showProjectScreen();
            continue;

        case 4:
            exit = TRUE;
            break;
        default:
            status = ERR;
            exit = TRUE;
        }
    }

    return main_menu_option;
};

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

    int EXIT = FALSE, title_width;
    char *question;
    char *answer;
    int c = wgetch(bot_win);
    while(!EXIT){
        question = "Digite o nome do projeto:";
        title_width = strlen(question);
        mvwprintw(bot_win, 4, (max_x - title_width) / 2, "%s", question);
        wrefresh(bot_win);
        scanw(answer);
        wrefresh(bot_win);
        if (c == 'j')
        {
            EXIT = TRUE;
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