#ifndef __TASK_LIST_H__

#define __TASK_LIST_H__ 


#include "Task.h"


typedef struct ElementTask{ 

    Task_t task;
    struct Element* next;

} ElementTask_t;

typedef ElementTask_t* TaskList_t; 


#endif