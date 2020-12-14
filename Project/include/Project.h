#ifndef __PROJECT_H__
#define __PROJECT_H__

#include <ncurses.h>

#define TITLE_SIZE 48
#define DESCRIPTION_SIZE 512
#define NAME_SIZE 64
#define EMAIL_SIZE 64

// char* com os tamanhos específicos de title e description
typedef char Description[DESCRIPTION_SIZE];
typedef char Title[TITLE_SIZE]; 
typedef char Name[NAME_SIZE]; 
typedef char Email[EMAIL_SIZE]; 

// Project struct
typedef struct Project_Element
{
    WINDOW *win;
    char *title;
    char *description;
    struct Project_Element *next;
    struct Collaborator_Element_t *firstCollaborator; // Ponteiro para o primeiro elemento da lista de colaboradores

} Project_Element_t;

typedef Project_Element_t *Project;

// Collaborator struct
typedef struct Collaborator_Element
{
    WINDOW *win;
    char *name;
    char *email;
    char *description;
    struct Collaborator_Element *next; 

} Collaborator_Element_t;

typedef Collaborator_Element_t *Collaborator;

// Functions
Project createProject(Title title, Description description);

int showProjects();

int createCollaborator(Name name, Email email, Description description, Project project);

int showProjectCollaborators(Project project, WINDOW *w);

int deleteProject(Project project);

int deleteCollaborator(Project protect, Collaborator collaborator);

int getNumbProjects();

#endif
