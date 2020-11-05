#include <stdio.h>
#include <stdlib.h>
#include "Project.h"

#define PROJECT_DISPLAY_WIDTH 25
#define PROJECT_DISPLAY_HEIGHT 6 

int lastWidth = 0;

Project createProject(Title title, Description description)
{
    if (strlen(title) >= TITLE_SIZE || strlen(description) >= DESCRIPTION_SIZE)
        return ERROR;
    Project project = (Project)malloc(sizeof(Project_Element_t));
    if (!project)
        return ERROR;
    project->title = title;
    project->description = description;
    CollaboratorsListElement collaboratorsListElement = (CollaboratorsListElement)malloc(sizeof(Collaborators_List_Element_t));
    if (!collaboratorsListElement)
        return ERROR;
    collaboratorsListElement->id = 0;
    collaboratorsListElement->collaborator = NULL;
    collaboratorsListElement->prev_collaboratorsListElement = NULL;
    collaboratorsListElement->next_collaboratorsListElement = NULL;
    project->collaboratorsListElement = collaboratorsListElement;
    return project;
}

int showProjects(WINDOW w)
{
    ProjectListElement actual = firstProject;
    int title_len;
    if (!actual)
        mvwprintw(w, 2, 3, "VAZIO");
        wrefresh(w);
        return SUCCESS;
    while (actual)
    {
        title_len = strlen(actual->project->title);
        actual->win = newwin(PROJECT_DISPLAY_HEIGHT, PROJECT_DISPLAY_WIDTH, 4, lastWidth + 1);
        refresh();
        box(actual->win, 0, 0);
        mvwprintw(actual->w, (PROJECT_DISPLAY_HEIGHT - 2)/2, (PROJECT_DISPLAY_WIDTH - title_len)/2, "%s", actual->project->title);
        wrefresh(actual->win);
        actual = actual->next_project;
        lastWidth += (PROJECT_DISPLAY_WIDTH + 1);
    }
    return SUCCESS;
}

int showProjectDetails(Project project)
{
    if (!project)
        return ERROR;
    CollaboratorsListElement actual = project->collaboratorsListElement;
    printf("\n\n%d | Projeto %s\nDescricao: %s\nColaboradores:", project->id, project->title, project->description);
    if (actual->collaborator == NULL)
        printf("Sem colaboradores.");
    while (actual)
    {
        printf("%s\n", actual->collaborator->name);
        actual = actual->next_collaboratorsListElement;
    }
    return SUCCESS
}

int showProjectCollaboratorsList(Project project)
{
    if (!project)
        return ERROR;
    CollaboratorsListElement actual = project->collaboratorsListElement;
    printf("\n\nColaboradores:");
    if (actual->collaborator == NULL)
        printf("Sem colaboradores.");
    while (actual)
    {
        printf("%sn", actual->collaborator->name);
        actual = actual->next_collaboratorsListElement;
    }
    return SUCCESS;
}

int showCollaboratorProfile(Project project, Name name)
{
    if (!project)
        return ERROR;
    CollaboratorsListElement actual = project->collaboratorsListElement;
    if (strlen(name) >= NAME_SIZE)
        return ERROR;
    while (actual)
    {
        if (!strcmp(name, actual->collaborator->name))
        {
            printf("\nNome: %s\nEmail: %s\nDescricao: %s\n", actual->collaborator->name, actual->collaborator->email, actual->collaborator->description);
            return SUCCESS;
        }
        else
        {
            actual = actual->next_collaboratorsListElement;
        }
    }
    return ERROR;
}

Collaborator createCollaboratorProfile(Name name, Email email, Description description)
{
    if (strlen(name) >= NAME_SIZE || strlen(email) >= EMAIL_SIZE || strlen(description) >= DESCRIPTION_SIZE)
        return ERROR;
    Collaborator collaborator = (Collaborator)malloc(sizeof(Collaborator_Element_t));
    if (!collaborator)
        return ERROR;
    collaborator->name = name;
    collaborator->email = email;
    collaborator->description = description;
    return collaborator;
}

int editCollaboratorProfile(Project project, Name name)
{
    if (!project)
        return ERROR;
    if (strlen(name) >= NAME_SIZE)
        return ERROR;
    CollaboratorsListElement actual = project->collaboratorsListElement;
    while (actual)
    {
        if (!strcmp(name, actual->collaborator->name))
        {
            printf("Nome: ");
            scanf(" %s", actual->collaborator->name);
            if (strlen(actual->collaborator->name) >= NAME_SIZE)
                return ERROR;
            printf("Email: ");
            scanf(" %s", actual->collaborator->email);
            if (strlen(actual->collaborator->email) >= EMAIL_SIZE)
                return ERROR;
            printf("Descricao: ");
            scanf(" %s", actual->collaborator->description);
            if (strlen(actual->collaborator->description) >= DESCRIPTION_SIZE)
                return ERROR;
            return SUCCESS;
        }
        else
        {
            actual = actual->next_collaboratorsListElement;
        }
    }
    return ERROR;
}

int pushProject(Project project)
{
    if (!project)
        return ERROR;
    ProjectListElement actual = firstProject;
    if (firstProject)
    {
        while (actual)
        {
            if (actual->next_project == NULL)
            {
                actual->next_project->id = actual->id + 1;
                actual->next_project->win = NULL;
                actual->next_project->project = project;
                actual->next_project->next_project = NULL;
                return SUCCESS;
            }
            actual = actual->next_project;
        }
    }
    else
    {
        firstProject->id = 1;
        firstProject->win = NULL;
        firstProject->next_project = NULL;
        firstProject->project = project;
    }
}

int deleteProject(Project project)
{
    ProjectListElement actual = firstProject, aux;
    if (!firstProject || !project)
        return ERROR;
    while (actual)
    {
        if (actual->next_project->project == project)
        {
            aux = actual->next_project;
            actual->next_project = aux->next_project;
            free(aux);
            return SUCCESS;
        }
        else
            actual = actual->next_project;
    }
    return ERROR;
}

int pushCollaborator(Project project, Collaborator collaborator)
{
    if (!project || !collaborator)
        return ERROR;
    CollaboratorsListElement actual = (CollaboratorsListElement)malloc(sizeof(Collaborators_List_Element_t));
    if (!actual)
        return ERROR;
    CollaboratorsListElement aux;
    actual = project->collaboratorsListElement;
    if (actual->collaborator == NULL)
    {
        actual->id = 1;
        actual->collaborator = collaborator;
        actual->prev_collaboratorsListElement = NULL;
        actual->next_collaboratorsListElement = NULL;
        return SUCCESS;
    }
    else
    {
        while (actual)
        {
            if (actual->next_collaboratorsListElement == NULL)
            {
                aux = actual->next_collaboratorsListElement;
                aux->id = actual->id + 1;
                aux->collaborator = collaborator;
                aux->prev_collaboratorsListElement = actual;
                aux->next_collaboratorsListElement = NULL;
                return SUCCESS;
            }
            actual = actual->next_collaboratorsListElement;
        }
    }
}

int deleteCollaborator(Project project, Collaborator collaborator)
{
    CollaboratorsListElement actual = project->collaboratorsListElement, aux, firstElement;
    firstElement = actual;
    if (!project || !collaborator || firstElement->id == 0)
        return ERROR;
    while (actual)
    {
        if (actual->next_collaboratorsListElement->collaborator == collaborator)
        {
            aux = actual->next_collaboratorsListElement;
            actual->next_collaboratorsListElement = aux->next_collaboratorsListElement;
            if (aux->next_collaboratorsListElement != NULL)
            {
                aux->next_collaboratorsListElement->prev_collaboratorsListElement = actual;
            }
            free(aux);
            return SUCCESS;
        }
        actual = actual->next_collaboratorsListElement;
    }
    return ERROR;
}

Collaborator searchCollaboratorByName(Project project, Name name)
{
    if (!project)
        return ERROR;
    CollaboratorsListElement actual = (CollaboratorsListElement)malloc(sizeof(Collaborators_List_Element_t));
    if (!actual)
        return ERROR;
    if (strlen(name) >= NAME_SIZE)
        return ERROR;
    actual = project->collaboratorsListElement;
    while (actual)
    {
        if (!strcmp(name, actual->collaborator->name))
        {
            return actual->collaborator;
        }
        else
        {
            actual = actual->next_collaboratorsListElement;
        }
    }
    return ERROR;
}

int showProjectTasklist(Project project);