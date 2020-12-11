#ifndef __TASK_LIST_H__

#define __TASK_LIST_H__ 

#include "utils.h"
#include "Task.h"

#define TASK_LIST_DISPLAY_WIDTH 20
#define TASK_LIST_DISPLAY_HEIGHT 30

typedef int ID;

typedef struct TaskElement {

    ID id;
    Task_t* task;

    struct TaskElement* next;
    struct TaskElement* prev;

} TaskElement_t;

typedef struct TaskList {
    WINDOW* win;
    int numbTasks;
    TaskElement_t* head;
} TaskList_t;


TaskList_t* createTaskList();

int deleteTaskList(TaskList_t* taskList);

Task_t* addTask(TaskList_t* taskList, Task_t* t);

int deleteTaskElement(TaskList_t* taskList, Task_t* t);

int moveTaskOnList(TaskList_t* taskList, Task_t* task, Task_t* after);

int deleteTaskElementById(TaskList_t* taskList, ID id);

int deleteTaskElementByTitle(TaskList_t* taskList, Title title);

int deleteTaskElementbyDescription(TaskList_t* taskList, Description description);

int showTaskList(TaskList_t* taskList, bool selected);

int hideTaskList(TaskList_t* taskList);

int moveTaskList(TaskList_t* taskList, bool selected);

#endif
