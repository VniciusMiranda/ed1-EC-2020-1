#ifndef __PROJECT_H__
#define __PROJECT_H__

#include <ncurses.h>

// movi as definições em project organizer para cá
//estava havendo conflito entre os tipos com os outros
// tipos abstratos :p
#define TITLE_SIZE 256
#define DESCRIPTION_SIZE 1024
#define NAME_SIZE 64
#define EMAIL_SIZE 64

// char* com os tamanhos específicos de title e description
typedef char Description[DESCRIPTION_SIZE];
typedef char Title[TITLE_SIZE]; 
typedef char Name[NAME_SIZE]; 
typedef char Email[EMAIL_SIZE]; 


// Project List struct
typedef struct Project_List_Element
{
    int id;
    WINDOW *win;
    struct Project project;
    struct Project_List_Element *next_project;
} Project_List_Element_t;

typedef Project_List_Element_t *ProjectListElement;

ProjectListElement firstProject = NULL;

// Project struct
typedef struct Project_Element
{
    Title title;
    Description description;
    struct CollaboratorsListElement collaboratorsListElement; // Ponteiro para o primeiro elemento da lista de colaboradores
} Project_Element_t;

typedef Project_Element_t *Project;

// Collaborator List struct
typedef struct Collaborators_List_Element
{
    int id;
    struct Collaborator collaborator;  // Perfil do colaborador
    struct Collaborators_List_Element *prev_collaboratorsListElement;
    struct Collaborators_List_Element *next_collaboratorsListElement;   // Ponteiro para a próxima struct da lista de colaborador com o ponteiro do próximo colaborador da lista
} Collaborators_List_Element_t;

typedef Collaborators_List_Element_t *CollaboratorsListElement;

// Collaborator struct
typedef struct Collaborator_Element
{
    Name name;
    Email email;
    Description description;
} Collaborator_Element_t;

typedef Collaborator_Element_t *Collaborator;

// Functions

Project createProject(Title title, Description description);

int showProjects();

int showProjectDetails(Project project);

int showProjectCollaboratorsList(Project project);

int showCollaboratorProfile(Project project, Name name);

Collaborator createCollaboratorProfile(Name name, Email email, Description description);

int editCollaboratorProfile(Project project, Name name);

int pushProject(Project project);

int deleteProject(Project project);

int pushCollaborator(Project protect, Collaborator collaborator);

int deleteCollaborator(Project protect, Collaborator collaborator);

Collaborator searchCollaboratorByName(Project project, Name name);

int showProjectTasklist(Project project);

int getNumbProjects();

#endif