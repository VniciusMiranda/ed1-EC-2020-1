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

    // Create the global window
    WINDOW *global_win = newwin(max_y, max_x, 0, 0);
    // Press 'esc'
    mvwprintw(global_win, 1, 1, "* Pressione 'esc' para cancelar e voltar");
    wrefresh(global_win);
    refresh();

    // Create the middle window
    WINDOW *mid_win = newwin(max_y / 2, max_x - 2, (max_y / 2) - (max_y / 4), 1);
    refresh();
    box(mid_win, 0, 0);
    mvwprintw(mid_win, 0, max_x / 2 - strlen("Crie seu Projeto") / 2, "Crie seu Projeto");
    wrefresh(mid_win);

    // Input Windows
    WINDOW *midI_win = newwin((max_y / 2) - 4, max_x / 3, ((max_y / 2) - (max_y / 4)) + 2, (max_x / 2) - ((max_x / 3) + 2) / 2);
    refresh();

    // decoration
    int tb = (int)' ';
    WINDOW *midD_win = newwin((max_y / 2) - 2, (max_x / 3) + 2, ((max_y / 2) - (max_y / 4)) + 1, ((max_x / 2) - ((max_x / 3) + 2) / 2) - 1);
    wborder(midD_win, 0, 0, tb, tb, tb, tb, tb, tb);
    wrefresh(midD_win);

    // Inputs
    int numCol, i;
    char *title = (char *)malloc(TITLE_SIZE * sizeof(char));
    char *description = (char *)malloc(DESCRIPTION_SIZE * sizeof(char));
    char *name = (char *)malloc(NAME_SIZE * sizeof(char));
    char *email = (char *)malloc(EMAIL_SIZE * sizeof(char));
    char *colDescription = (char *)malloc(DESCRIPTION_SIZE * sizeof(char));

    echo();

    // --- TITLE ---
    mvwprintw(midI_win, 1, 1, "Digite o nome do projeto:");
    wrefresh(midI_win);
    mvwscanw(midI_win, 1, 2 + strlen("Digite o nome do projeto:"), "%s", &title[0]);
    wrefresh(midI_win);

    if (strlen(title) > TITLE_SIZE)
    {
        goBack(mid_win);
        return;
    }
    // --- END TITLE ---

    // --- COLLABORATORS ---
    mvwprintw(midI_win, 5, 1, "Digite a quantidade de colaboradores iniciais:");
    wrefresh(midI_win);
    mvwscanw(midI_win, 5, 2 + strlen("Digite a quantidade de colaboradores iniciais:"), "%d", &numCol);
    wrefresh(midI_win);

    if (numCol > 20)
    {
        mvwprintw(mid_win, 12, 12, "Número máximo de colaboradores excedido, tente novamente.");
        mvwprintw(mid_win, 14, 12, "Pressione uma tecla para sair.");
        wrefresh(mid_win);
        refresh();
        int c = wgetch(mid_win);
        noecho();
        clear();
        refresh();
        return;
    }

    // --- END COLLABORATORS ---

    // --- DESCRIPTION ---
    mvwprintw(midI_win, 9, 1, "Digite uma breve descrição do Projeto:");
    wrefresh(midI_win);
    mvwscanw(midI_win, 9, 2 + strlen("Digite uma breve descrição do Projeto:"), "%s", &description[0]);
    wrefresh(midI_win);

    if (strlen(description) > DESCRIPTION_SIZE)
    {
        goBack(mid_win);
        return;
    }
    // --- END DESCRIPTION ---

    // Create Project
    Project project = createProject(title, description);
    if (!project)
    {
        wrong(mid_win);
        return;
    }

    refresh();

    // Create Collaborator
    int clearVar, statusCollaborator;
    for (i = 0; i < numCol; i++)
    {
        clearVar = clearWin(midI_win, (max_y / 2) - 6, max_x / 3);
        if (clearVar == ERR)
        {
            wrong(mid_win);
            break;
        }

        refresh();

        mvwprintw(midI_win, 1, 1, "Digite o nome do colaborador:");
        wrefresh(midI_win);
        mvwscanw(midI_win, 1, 2 + strlen("Digite o nome do colaborador:"), "%s", &name[0]);
        wrefresh(midI_win);

        if (strlen(name) > NAME_SIZE)
        {
            goBack(mid_win);
            return;
        }

        mvwprintw(midI_win, 5, 1, "Digite o email do colaborador:");
        wrefresh(midI_win);
        mvwscanw(midI_win, 5, 2 + strlen("Digite o email do colaborador:"), "%s", &email[0]);
        wrefresh(midI_win);

        if (strlen(email) > EMAIL_SIZE)
        {
            goBack(mid_win);
            return;
        }

        mvwprintw(midI_win, 9, 1, "Digite a descrição do colaborador:");
        wrefresh(midI_win);
        mvwscanw(midI_win, 9, 2 + strlen("Digite a descrição do colaborador:"), "%s", &colDescription[0]);
        wrefresh(midI_win);

        if (strlen(colDescription) > DESCRIPTION_SIZE)
        {
            goBack(mid_win);
            return;
        }

        statusCollaborator = createCollaborator(name, email, description, project);
        if (statusCollaborator == ERR)
        {
            wrong(mid_win);
            return;
        }
    }

    title = NULL;
    description = NULL;
    colDescription = NULL;
    name = NULL;
    email = NULL;
    noecho();

    mvwprintw(mid_win, 13, 14, "O PROJETO FOI CRIADO COM SUCESSO!");
    wrefresh(mid_win);
    refresh();

    // Creating Select Menu
    char *options[] = {"Criar tarefas para este projeto", "Criar outro projeto", "Excluir projeto", "Voltar para o menu"};
    char *question;
    int num_options;
    int choice;

    question = "Selecione uma opção:";
    num_options = sizeof(options) / sizeof(char *);
    int exit = FALSE;

    while (!exit)
    {
        choice = selectWin(options, question, num_options, (max_y / 2) - (max_y / 4) + 8, max_x / 2 + max_x / 4 - 2, max_x / 5, max_y / 2 - max_y / 4 - 5, 0);

        switch (choice)
        {
        case 0:
            clear();
            refresh();
            // IR PARA TELA DE TASKS
            exit = TRUE;
            break;
        case 1:
            clear();
            refresh();
            createProjectScreen();
            exit = TRUE;
            break;
        case 2:
            if (!project)
            {
                mvwprintw(mid_win, 12, 12, "                                         "); //provisório
                mvwprintw(mid_win, 13, 12, "                                         "); //provisório
                mvwprintw(mid_win, 14, 12, "                                         "); //provisório
                mvwprintw(mid_win, 11, 12, "Falha ao excluir projeto.");
                mvwprintw(mid_win, 13, 12, "O projeto já foi excluído.");
                mvwprintw(mid_win, 15, 12, "Pressione uma tecla para sair.");
                wrefresh(mid_win);
                refresh();
                int c = wgetch(mid_win);
                clear();
                refresh();
                exit = TRUE;
                break;
            }
            int del = deleteProject(project);
            if (del == ERR)
            {
                mvwprintw(mid_win, 13, 12, "                                         "); //provisório
                mvwprintw(mid_win, 12, 12, "Falha ao excluir projeto.");
                mvwprintw(mid_win, 14, 12, "Pressione uma tecla para sair.");
                wrefresh(mid_win);
                refresh();
                int c = wgetch(mid_win);
                clear();
                refresh();
                exit = TRUE;
                break;
            }
            mvwprintw(mid_win, 13, 12, "                                         "); //provisório
            mvwprintw(mid_win, 12, 12, "Sucesso ao excluir projeto.");
            mvwprintw(mid_win, 14, 12, "Pressione uma tecla para sair.");
            wrefresh(mid_win);
            refresh();
            int c = wgetch(mid_win);
            clear();
            refresh();
            exit = TRUE;
            break;
        case 3:
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

void showProjectScreen()
{
    // Clear the screen
    clear();
    refresh();

    // Gets the height and width
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // Create the top window
    WINDOW *top_win = newwin(max_y / 2 - 2, max_x - 2, 1, 1);
    refresh();
    box(top_win, 0, 0);
    wprintw(top_win, "Projetos");
    int process = showProjects(top_win);
    wrefresh(top_win);
    refresh();

    // Create the half-screen windows
    WINDOW *botL_win = newwin((max_y / 2 - 2), (max_x / 2) - 1, (max_y / 2) + 1, 1);
    refresh();
    box(botL_win, 0, 0);
    wrefresh(botL_win);

    WINDOW *botR_win = newwin((max_y / 2 - 2), (max_x / 2) - 1, (max_y / 2) + 1, (max_x / 2) + 1);
    refresh();
    box(botR_win, 0, 0);
    wrefresh(botR_win);

    char *question;
    int num_options;
    int title_width;
    int choice;
    int nProjects = getNumbProjects();

    if (process == ERR)
    {
        char *options[] = {"Criar um novo projeto", "Voltar para o menu"};
        question = "Selecione uma opção:";
        num_options = sizeof(options) / sizeof(char *);
        title_width = (strlen(question) + 10) / 2;
        choice = selectWin(options, question, num_options, max_y * 5 / 8, max_x / 4 - title_width, 0, 0, 0);

        switch (choice)
        {
        case 0:
            clear();
            refresh();
            createProjectScreen();
            break;
        default:
            clear();
            refresh();
        }
    }
    else
    {
        char *options[] = {};
        for (int i = 0; i < nProjects; i++)
        {
            options[i] = strcat("Projeto ", (char)(i + 1));
        }
        question = "Selecione um projeto:";
        num_options = sizeof(options) / sizeof(char *);
        title_width = (strlen(question) + 10) / 2;
        choice = selectWin(options, question, num_options, max_y * 5 / 8, max_x / 4 - title_width, 0, 0, 0);
    }
}

void goBack(WINDOW *w)
{
    mvwprintw(w, 12, 12, "O valor que você digitou não é permitido.");
    mvwprintw(w, 14, 12, "Pressione uma tecla para sair.");
    wrefresh(w);
    refresh();
    int c = wgetch(w);
    noecho();
    clear();
    refresh();
}

void wrong(WINDOW *w)
{
    mvwprintw(w, 12, 12, "Algo deu errado, tente novamente.");
    mvwprintw(w, 14, 12, "Pressione uma tecla para sair.");
    wrefresh(w);
    refresh();
    int c = wgetch(w);
    noecho();
    clear();
    refresh();
}

void clearLeftSide(){}