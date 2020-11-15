#ifndef __TASK_H__
#define __TASK_H__


#include "ProjectOrganizer.h"

#include "Label.h"
#include "Display.h"


#define LABELS_MAX 4 


#define TASK_DISPLAY_WIDTH 25 
#define TASK_DISPLAY_HEIGHT 6

typedef char Title[TASK_DISPLAY_WIDTH];

typedef struct Task{

    Title title;
    Description description;
    bool available_colors[NUMB_COLORS];


    Label_t* labels[LABELS_MAX];
    int numb_labels;


    WINDOW* win;

} Task_t;


Task_t* createTask(char* title, char* description);


int deleteTask(Task_t* t);


int addLabel(Task_t* t, Label_t* label);


int show(Task_t* t, unsigned int y, unsigned x, bool selected);


int hide(Task_t* t);


bool isDisplayed(Task_t* t);


int moveTask(Task_t* t, int y, int x, bool selected);


int setDescription(Task_t* t, char* d);


int setTitle(Task_t* t, char* title);


char* getDescription(Task_t* t);


char* getTitle(Task_t* t);


#endif