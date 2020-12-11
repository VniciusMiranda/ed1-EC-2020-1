#include "Task.h"

static void _initAvailableColors(Task_t* t);

static void _updateLabelArray(Task_t* t, int index);

static void _initLabelArray(Task_t* t);

static int _displayLabels(Task_t* t);

static int _copyLabelArray(Label_t* src, Label_t* dest);

static int _copyAvailableColors(bool* src, bool* dest);


Task_t* createTask(char* title, char* description){
    if(strlen(title) >= TASK_DISPLAY_WIDTH)
        return NULL;

    Task_t* new_task = (Task_t*) malloc(sizeof(Task_t));
    if(!new_task) return NULL;

    setDescription(new_task, description);
    setTitle(new_task, title);

    _initLabelArray(new_task);
    _initAvailableColors(new_task);

    new_task->numb_labels = 0;
    new_task->win = NULL;

    return new_task;
}


int deleteTask(Task_t* t) {
    if(isNullPointer(t)) return ERR;
    if(isDisplayed(t)) hide(t);
    free(t);
    return OK;
}


Task_t* copyTask(Task_t* t) {
    if(isNullPointer(t)) return NULL;

    Task_t* copy = createTask(t->title, t->description);

    copy->numb_labels = t->numb_labels;
    copy->win = NULL;

    _copyAvailableColors(copy->available_colors, t->available_colors);
    _copyLabelArray(copy->labels, t->labels);

    return copy;
}


int addLabel(Task_t* t, Label_t* label){
    if(isNullPointer(t) || isNullPointer(label))  
        return ERR;

    if(t->numb_labels >= LABELS_MAX || isColorNotAvailable(t, label->color)) 
        return ERR;

    t->available_colors[label->color] = FALSE;
    t->labels[t->numb_labels++] = label;

    return OK;
}


int removeLabel(Task_t* t, LabelName label_name){

    for(int i = 0; i < t->numb_labels; i++)
    {
        if(equals(t->labels[i]->name, label_name)) 
        {
            deleteLabel(t->labels[i]);
            t->labels[i] = NULL;

            _updateLabelArray(t, i);
            t->numb_labels--;

            return OK; 
        }
    }
    return ERR;
}


int showTask(Task_t* t, unsigned int y, unsigned x, bool selected){
    if(isNullPointer(t)) return ERR; 

    if(isNotDisplayed(t)) 
        t->win = newwin(TASK_DISPLAY_HEIGHT, TASK_DISPLAY_WIDTH, y, x);    
    refresh();

    box(t->win, 0, 0); 
    int xMiddle = (TASK_DISPLAY_WIDTH - strlen(t->title))/2;

    if(selected)
       wattron(t->win, A_REVERSE);

    mvwprintw(t->win, 0, xMiddle, "%s", t->title);
    wattroff(t->win, A_REVERSE);

    if(t->numb_labels) _displayLabels(t); 
    wrefresh(t->win);

    return OK;
}


int hideTask(Task_t* t) {
    if(isNullPointer(t) || isNotDisplayed(t)) return ERR; 

    eraseWin(t->win, TASK_DISPLAY_HEIGHT, TASK_DISPLAY_WIDTH);
    t->win = NULL;
}


int moveTask(Task_t* t, int y, int x, bool selected) {
    if(isNullPointer(t) || isNotDisplayed(t))
        return ERR;

    hide(t);
    show(t, y, x, selected);

    return OK;
}


int setDescription(Task_t* t, char* d) {
    if(isNullPointer(t) || strlen(d) >= TASK_DESCRIPTION_SIZE) return ERR;
    strcpy(t->description, d);

    return OK;
}


char* getDescription(Task_t* t) {
    return !t ? (char*) ERR : t->description;
}


int setTitle(Task_t* t, char* title) {
    if(isNullPointer(t) || strlen(title) >= TASK_DISPLAY_WIDTH) return ERR;
    strcpy(t->title, title);

    return OK;
}


char* getTitle(Task_t* t) {
    return isNullPointer(t) ? NULL : t->title;
}


bool isDisplayed(Task_t* t) {
    return !isNullPointer(t) ? TRUE : FALSE;
}


bool isNotDisplayed(Task_t* t) {
    return isNullPointer(t) ? TRUE : FALSE;
}


bool isColorAvailable(Task_t* t, Color color) {
    return t->available_colors[color] ? TRUE : FALSE;
}


bool isColorNotAvailable(Task_t* t, Color color) {
    return !t->available_colors[color] ? TRUE : FALSE;
}


static int _displayLabels(Task_t* t) {

    Color labelColor;
    for(int i = 0; i < t->numb_labels && i < TASK_DISPLAY_LIMIT_Y; i++)
    {
        labelColor = t->labels[i]->color;

        wmove(t->win, 1 + i, 1);
        printWithColor(t->win, labelColor, t->labels[i]->name);
    }
    if(t->numb_labels >= TASK_DISPLAY_LIMIT_Y)
            wprintw(t->win, "%s", " ...");
}


static void _initAvailableColors(Task_t* t) {
    for(int i = 0; i < NUMB_COLORS; i++) 
        t->available_colors[i] = TRUE;
}


static void _initLabelArray(Task_t* t) {
    for(int i = 0; i < LABELS_MAX; i++) 
        t->labels[i] = NULL;
}


static int _copyLabelArray(Label_t* dest, Label_t* src){
    if(isNullPointer(src) || isNullPointer(dest)) return ERR;

    for(int i = 0; i < LABELS_MAX; i++)  copyLabel(dest + i, src + i);

    return OK;
}


static int _copyAvailableColors(bool* dest, bool* src){
    if(isNullPointer(src) || isNullPointer(dest)) return ERR;

    for(int i = 0; i < NUMB_COLORS; i++) dest[i] = src[i];
    return OK;
}


static void _updateLabelArray(Task_t* t, int index) {
    for(int i = index; i < LABELS_MAX - 1; i++)
        t->labels[i] = t->labels[i + 1];
}
