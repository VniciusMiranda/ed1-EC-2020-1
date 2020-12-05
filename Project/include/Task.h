#ifndef __TASK_H__ 

#define __TASK_H__

#include "Display.h"
#include "Label.h"
#include "utils.h"

#define LABELS_MAX 5 

#define TASK_DISPLAY_WIDTH 25 
#define TASK_DISPLAY_HEIGHT 6

#define TASK_DISPLAY_LIMIT_Y TASK_DISPLAY_HEIGHT - 2 

#define TASK_TITLE_SIZE TASK_DISPLAY_WIDTH
#define TASK_DESCRIPTION_SIZE TASK_DISPLAY_WIDTH*10

typedef char Title[TASK_TITLE_SIZE];
typedef char Description[TASK_DESCRIPTION_SIZE];

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

int removeLabel(Task_t* t, LabelName label_name);

bool isColorAvailable(Task_t* t, Color color);

bool isColorNotAvailable(Task_t* t, Color color);

int show(Task_t* t, unsigned int y, unsigned x, bool selected);

int hide(Task_t* t);

bool isDisplayed(Task_t* t);

bool isNotDisplayed(Task_t* t);

int moveTask(Task_t* t, int y, int x, bool selected);

int setDescription(Task_t* t, char* d);

char* getDescription(Task_t* t);

int setTitle(Task_t* t, char* title);

char* getTitle(Task_t* t);

#endif