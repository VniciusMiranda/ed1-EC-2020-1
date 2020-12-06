#include <stdlib.h>
#include <string.h>
#include "Project.h"

#define PROJECT_DISPLAY_WIDTH 25
#define PROJECT_DISPLAY_HEIGHT 16

int lastWidth = 0;
Project firstProject = NULL;

//OK
int createProject(Title title, Description description, Collaborator collaborator)
{
    if (strlen(title) >= TITLE_SIZE || strlen(description) >= DESCRIPTION_SIZE)
        return ERR;
    if (!collaborator)
        return ERR;

    Project project = (Project)malloc(sizeof(Project_Element_t));
    if (!project)
        return ERR;
    project->title = title;
    project->description = description;

    project->win = NULL;
    project->next = NULL;
    project->firstCollaborator = collaborator;
    if(!firstProject){
        firstProject = project;
    }
        Project actual = firstProject;
        while(actual)
        {   
            if(!actual->next){
                actual->next = project;
                return OK;
            }
            actual = actual->next;
        }
    return OK;
}

//OK
int showProjects(WINDOW *w)
{
    Project actual = firstProject;

    int title_len;
    if (!actual)
    {
        mvwprintw(w, 2, 3, "VAZIO");
        return ERR;
    }
    while (actual)
    {

        title_len = strlen(actual->title);
        actual->win = newwin(PROJECT_DISPLAY_HEIGHT, PROJECT_DISPLAY_WIDTH, 4, lastWidth + 1);
        refresh();
        box(actual->win, 0, 0);
        mvwprintw(actual->win, 0, (PROJECT_DISPLAY_WIDTH - title_len) / 2, "%s", actual->title);
        mvwprintw(actual->win, 4, 2, "Descrição");
        mvwprintw(actual->win, 6, 2, "%s", actual->description);
        wrefresh(actual->win);
        actual = actual->next;
        lastWidth += (PROJECT_DISPLAY_WIDTH + 1);
    }
    lastWidth = 0;
    return OK;
}

int createCollaborator(Name name, Email email, Description description, Project project)
{
    if (strlen(name) > NAME_SIZE || strlen(email) > EMAIL_SIZE || strlen(description) > DESCRIPTION_SIZE || !project)
        return ERR;
    Collaborator collaborator = (Collaborator)malloc(sizeof(Collaborator_Element_t));
    if (!collaborator)
        return ERR;
    collaborator->name = name;
    collaborator->email = email;
    collaborator->description = description;
    collaborator->next = NULL;
    collaborator->win = NULL;
    if(!project->firstCollaborator){
        project->firstCollaborator = collaborator;
    }
        Collaborator actual = project->firstCollaborator;
        while(actual)
        {   
            if(!actual->next){
                actual->next = collaborator;
                return OK;
            }
            actual = actual->next;
        }
    return OK;
}

int showProjectCollaborators(Project project, WINDOW *w)
{
    if (!project || !w)
        return ERR;
    Collaborator actual = project->firstCollaborator;
    int title_len;
    mvwprintw(w, 2, 3, "Colaboradores");
    if (!actual)
        mvwprintw(w, 6, 3, "Sem colaboradores");
    while (actual)
    {
        title_len = strlen(project->title);
        actual->win = newwin(PROJECT_DISPLAY_HEIGHT, PROJECT_DISPLAY_WIDTH, 4, lastWidth + 1);
        refresh();
        box(actual->win, 0, 0);
        mvwprintw(actual->win, 0, (PROJECT_DISPLAY_WIDTH - title_len) / 2, "%s", project->title);
        mvwprintw(actual->win, 4, 2, "Nome:");
        mvwprintw(actual->win, 6, 2, "%s", actual->name);
        mvwprintw(actual->win, 8, 2, "E-mail:");
        mvwprintw(actual->win, 10, 2, "%s", actual->email);
        mvwprintw(actual->win, 12, 2, "Descrição:");
        mvwprintw(actual->win, 14, 2, "%s", actual->description);
        wrefresh(actual->win);
        actual = actual->next;
        lastWidth += (PROJECT_DISPLAY_WIDTH + 1);
    }
    lastWidth = 0;
    return OK;
}

/*

int editCollaboratorProfile(Project project, Name name)
{
    if (!project)
        return ERR;
    if (strlen(name) >= NAME_SIZE)
        return ERR;
    CollaboratorsListElement actual = project->collaboratorsListElement;
    while (actual)
    {
        if (!strcmp(name, actual->collaborator->name))
        {
            printf("Nome: ");
            scanf(" %s", actual->collaborator->name);
            if (strlen(actual->collaborator->name) >= NAME_SIZE)
                return ERR;
            printf("Email: ");
            scanf(" %s", actual->collaborator->email);
            if (strlen(actual->collaborator->email) >= EMAIL_SIZE)
                return ERR;
            printf("Descricao: ");
            scanf(" %s", actual->collaborator->description);
            if (strlen(actual->collaborator->description) >= DESCRIPTION_SIZE)
                return ERR;
            return OK;
        }
        else
        {
            actual = actual->next_collaboratorsListElement;
        }
    }
    return ERR;
}

*/

int deleteProject(Project project)
{
    Project actual = firstProject, aux;
    if (!firstProject || !project)
        return ERR;

    if (actual == project)
    {
        if (actual->next == NULL)
        {
            firstProject = NULL;
        }
        else
        {
            firstProject = actual->next;
            free(actual);
        }
        return OK;
    }
    while (actual)
    {
        if (actual->next == project)
        {
            aux = actual->next;
            actual->next = aux->next;
r
            free(aux);
            return OK;
        }
        else
            actual = actual->next;
    }
    return ERR;
}


int deleteCollaborator(Project project, Collaborator collaborator)
{
    Collaborator actual = project->firstCollaborator, aux;
    if (!project || !collaborator)
        return ERR;
    if (actual == collaborator)
    {
        aux = actual;
        if (actual->next != NULL)
        {
            free(aux);
        }
        else
        {
            actual = NULL;
        }
        return OK;
    }
    while (actual)
    {
        if (actual->next == collaborator)
        {
            aux = actual->next;
            actual->next = aux->next;
            if (aux->next != NULL)
            {
                aux->next = actual;

            }
            free(aux);
            return OK;
        }
        actual = actual->next;

    }
    return ERR;
}

//OK
int getNumbProjects()
{

    Project actual = firstProject;
    int n = 0;
    if (firstProject)
    {
        while (actual)
        {
            n++;
            if (actual->next == NULL)
            {
                return n;
            }
            actual = actual->next;
        }
    }
    else
    {
        return n;
    }
}

int showProjectTasklist(Project project);
