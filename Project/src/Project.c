#include <stdio.h>
#include <stdlib.h>
#include "Project.h"

#define PROJECT_DISPLAY_WIDTH 25
#define PROJECT_DISPLAY_HEIGHT 6

int lastWidth = 0;

//OK
Project createProject(Title title, Description description)
{
    if (strlen(title) >= TITLE_SIZE || strlen(description) >= DESCRIPTION_SIZE)
        return ERR;
    Project project = (Project)malloc(sizeof(Project_Element_t));
    if (!project)
        return ERR;
    project->title = title;
    project->description = description;
    CollaboratorsListElement collaboratorsListElement = (CollaboratorsListElement)malloc(sizeof(Collaborators_List_Element_t));
    if (!collaboratorsListElement)
        return ERR;
    collaboratorsListElement->id = 0;
    collaboratorsListElement->collaborator = NULL;
    collaboratorsListElement->prev_collaboratorsListElement = NULL;
    collaboratorsListElement->next_collaboratorsListElement = NULL;
    project->collaboratorsListElement = collaboratorsListElement;
    return project;
}

//OK
int showProjects(WINDOW w)
{
    ProjectListElement actual = firstProject;
    int title_len;
    if (!actual)
    {
        mvwprintw(w, 2, 3, "VAZIO");
        return ERR;
    }
    while (actual)
    {
        title_len = strlen(actual->project->title);
        actual->win = newwin(PROJECT_DISPLAY_HEIGHT, PROJECT_DISPLAY_WIDTH, 4, lastWidth + 1);
        refresh();
        box(actual->win, 0, 0);
        mvwprintw(actual->w, (PROJECT_DISPLAY_HEIGHT - 2) / 2, (PROJECT_DISPLAY_WIDTH - title_len) / 2, "%s", actual->project->title);
        wrefresh(actual->win);
        actual = actual->next_project;
        lastWidth += (PROJECT_DISPLAY_WIDTH + 1);
    }
    return OK;
}

int showProjectDetails(Project project)
{
    if (!project)
        return ERR;
    CollaboratorsListElement actual = project->collaboratorsListElement;
    printf("\n\n%d | Projeto %s\nDescricao: %s\nColaboradores:", project->id, project->title, project->description);
    if (actual->collaborator == NULL)
        printf("Sem colaboradores.");
    while (actual)
    {
        printf("%s\n", actual->collaborator->name);
        actual = actual->next_collaboratorsListElement;
    }
    return OK
}

int showProjectCollaboratorsList(Project project)
{
    if (!project)
        return ERR;
    CollaboratorsListElement actual = project->collaboratorsListElement;
    printf("\n\nColaboradores:");
    if (actual->collaborator == NULL)
        printf("Sem colaboradores.");
    while (actual)
    {
        printf("%sn", actual->collaborator->name);
        actual = actual->next_collaboratorsListElement;
    }
    return OK;
}

int showCollaboratorProfile(Project project, Name name)
{
    if (!project)
        return ERR;
    CollaboratorsListElement actual = project->collaboratorsListElement;
    if (strlen(name) >= NAME_SIZE)
        return ERR;
    while (actual)
    {
        if (!strcmp(name, actual->collaborator->name))
        {
            printf("\nNome: %s\nEmail: %s\nDescricao: %s\n", actual->collaborator->name, actual->collaborator->email, actual->collaborator->description);
            return OK;
        }
        else
        {
            actual = actual->next_collaboratorsListElement;
        }
    }
    return ERR;
}

Collaborator createCollaboratorProfile(Name name, Email email, Description description)
{
    if (strlen(name) >= NAME_SIZE || strlen(email) >= EMAIL_SIZE || strlen(description) >= DESCRIPTION_SIZE)
        return ERR;
    Collaborator collaborator = (Collaborator)malloc(sizeof(Collaborator_Element_t));
    if (!collaborator)
        return ERR;
    collaborator->name = name;
    collaborator->email = email;
    collaborator->description = description;
    return collaborator;
}

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

//OK
int pushProject(Project project)
{
    if (!project)
        return ERR;

    ProjectListElement new_project_element = (ProjectListElement)malloc(sizeof(Project_List_Element_t));
    if (!new_project_element)
        return ERR;

    ProjectListElement actual = firstProject;

    new_project_element->id = 1;
    new_project_element->win = NULL;
    new_project_element->next_project = NULL;
    new_project_element->project = project;

    if (firstProject)
    {
        while (actual)
        {
            if (actual->next_project == NULL)
            {
                new_project_element->id = actual->id + 1;
                actual->next_project = new_project_element;
                return OK;
            }
            actual = actual->next_project;
        }
    }
    else
    {
        firstProject = new_project_element;
        return OK;
    }
}

//Ok mas arrumar os ids
int deleteProject(Project project)
{
    ProjectListElement actual = firstProject, aux;
    if (!firstProject || !project)
        return ERR;

    if (actual->project == project)
    {
        if (actual->next_project == NULL)
        {
            firstProject = NULL;
        }
        else
        {
            firstProject = actual->next_project;
            free(actual);
        }
        return OK;
    }
    while (actual)
    {
        if (actual->next_project->project == project)
        {
            aux = actual->next_project;
            actual->next_project = aux->next_project;
            free(aux);
            return OK;
        }
        else
            actual = actual->next_project;
    }
    return ERR;
}

//OK
int pushCollaborator(Project project, Collaborator collaborator)
{
    if (!project || !collaborator)
        return ERR;
    CollaboratorsListElement aux = (CollaboratorsListElement)malloc(sizeof(Collaborators_List_Element_t));
    if (!aux)
        return ERR;
    CollaboratorsListElement actual = project->collaboratorsListElement;
    if (actual->collaborator == NULL)
    {
        aux->id = 1;
        aux->collaborator = collaborator;
        aux->prev_collaboratorsListElement = NULL;
        aux->next_collaboratorsListElement = NULL;
        project->collaboratorsListElement = aux;
        return OK;
    }
    else
    {
        while (actual)
        {
            if (actual->next_collaboratorsListElement == NULL)
            {
                aux->id = actual->id + 1;
                aux->collaborator = collaborator;
                aux->prev_collaboratorsListElement = actual;
                aux->next_collaboratorsListElement = NULL;
                actual->next_collaboratorsListElement = aux;
                return OK;
            }
            actual = actual->next_collaboratorsListElement;
        }
    }
}

//Ok mas arrumar os IDs
int deleteCollaborator(Project project, Collaborator collaborator)
{
    CollaboratorsListElement actual = project->collaboratorsListElement, aux;
    if (!project || !collaborator || actual->id == 0)
        return ERR;
    if (actual->collaborator == collaborator)
    {
        aux = actual;
        if (actual->next_collaboratorsListElement != NULL)
        {
            actual->next_collaboratorsListElement->prev_collaboratorsListElement = NULL;
            actual = actual->next_collaboratorsListElement;
            free(aux);
        }
        else
        {
            actual->id = 0;
            actual->collaborator = NULL;
        }
        return OK;
    }
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
            return OK;
        }
        actual = actual->next_collaboratorsListElement;
    }
    return ERR;
}

Collaborator searchCollaboratorByName(Project project, Name name)
{
    if (!project)
        return ERR;
    CollaboratorsListElement actual = (CollaboratorsListElement)malloc(sizeof(Collaborators_List_Element_t));
    if (!actual)
        return ERR;
    if (strlen(name) >= NAME_SIZE)
        return ERR;
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
    return ERR;
}

//OK
int getNumbProjects()
{
    ProjectListElement actual = firstProject;
    int n = 0;
    if (firstProject)
    {
        while (actual)
        {
            n++;
            if (actual->next_project == NULL)
            {
                return n;
            }
            actual = actual->next_project;
        }
    }
    else
    {
        return n;
    }
}

int showProjectTasklist(Project project);