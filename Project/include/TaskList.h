#ifndef __TASK_LIST_H__

#define __TASK_LIST_H__ 


#include "Task.h"

#define TASK_LIST_DISPLAY_WIDTH 20
#define TASK_LIST_DISPLAY_HEIGHT 30

typedef struct TaskElement {

    Task_t* task;
    struct TaskElement* next;
    struct TaskElement* prev;
} TaskElement_t;

typedef struct TaskList {

    int numbTasks;
    TaskElement_t* head;

    WINDOW* win;
} TaskList_t;


TaskList_t* createTaskList();

int deleteTaskList(TaskList_t* taskList);

Task_t* addTask(TaskList_t* taskList, Task_t* t);

int deleteTaskElement(TaskList_t* taskList, Task_t* t);

int deleteTaskElementByTitle(TaskList_t* taskList, Title title);


#endif
