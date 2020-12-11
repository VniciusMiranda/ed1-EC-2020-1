#include "TaskList.h"


bool static _isHeadNode(TaskList_t* taskList, TaskElement_t* element) {
    return taskList->head == element;
}


bool static _isFirstNode(TaskElement_t* element) {
    return isNullPointer(element) ? FALSE : element->next == NULL;
}


bool static _isLastNode(TaskElement_t* element) {
    return isNullPointer(element) ? FALSE : element->prev == NULL; 
}


int static _deleteNode(TaskList_t* taskList, TaskElement_t* del_element) {
    if (isNullPoitner(taskList) || isNullPointer(del_element))
        return ERR;

    if(_isHeadNode(taskList, del_element)) 
        taskList->head = del_element->next;

    if(!_isFirstNode(del_element)) 
        del_element->next->prev = del_element->prev;

    if (!_isLastNode(del_element)) 
        del_element->prev->next = del_element->next;

    if(errorIn(deleteTask(del_element->task))) return ERR;

    free(del_element); 

    return OK;
}


TaskList_t* createTaskList() {
    TaskList_t* newTaskList = (TaskList_t*) malloc(sizeof(TaskList_t));
    if(isNullPointer(newTaskList)) return NULL;

    newTaskList->head = NULL;
    newTaskList->win = NULL;
    newTaskList->numbTasks = 0;

    return newTaskList;
}


int destroyTaskList(TaskList_t* taskList) {
    if(isNullPointer(taskList)) return ERR;

    TaskElement_t* aux = taskList->head, *del;
    while(aux) 
    {
        if(errorIn(deleteTask(aux->task))) return ERR;
        del = aux;  
        aux = aux->next;
        free(del);
    }

    return OK;
}


Task_t* insertTaskAtEnd(TaskList_t* taskList, Task_t* t) {
    if(isNullPointer(taskList)) return NULL;

    TaskElement_t* new_element = (TaskElement_t*) malloc(sizeof(TaskElement_t));
    if(isNullPointer(new_element)) return NULL;

    new_element->task = t;
    new_element->next = NULL;

    if(isNullPointer(taskList->head))
    {
        new_element->prev = NULL;
        taskList->head = new_element;
        return OK;
    }

    TaskElement_t* element = taskList->head; 

    while(element->next) element = element->next;

    element->next = new_element;
    new_element->prev = element;
    taskList->numbTasks++;

    return OK;
}




int deleteTaskElement(TaskList_t* taskList, Task_t* t){
    if(isNullPointer(taskList) || isNullPointer(t)) return NULL;

    TaskElement_t* element = taskList->head;
    do {
        if(element->task == t) return _deleteNode(taskList, element);
        element = element->next;

    } while(element);

    return ERR;
}


int moveTaskOnList(TaskList_t* taskList, Task_t* task, Task_t* after){
    if(isNullPointer(taskList) || isNullPointer(task) || isNullPointer(after)) return ERR;

    if(errorIn(deleteTaskElement(taskList, task))) return ERR; 

    return OK;
}

int deleteTaskElementById(TaskList_t* taskList, ID id){
    if(isNullPointer(taskList)) return NULL;

    TaskElement_t* element = taskList->head;
    do {
        if(element->id == id) return _deleteNode(taskList, element);
        element = element->next;
    } while(element);

    return ERR;
}


int deleteTaskElementByTitle(TaskList_t* taskList, Title title){
    if(isNullPointer(taskList)) return NULL;

    TaskElement_t* element = taskList->head;
    do {
        if(equals(element->task->title, title)) return _deleteNode(taskList, element);
        element = element->next;
    } while(element);

    return ERR;
}


int deleteTaskElementbyDescription(TaskList_t* taskList, Description description){
    if(isNullPointer(taskList)) return NULL;

    TaskElement_t* element = taskList->head;
    do {
        if(equals(element->task->title, description)) return _deleteNode(taskList, element);
        element = element->next;
    } while(element);

    return ERR;
}


int showTaskList(TaskList_t* taskList, bool selected);


int hideTaskList(TaskList_t* taskList);


int moveTaskList(TaskList_t* taskList, bool selected);
