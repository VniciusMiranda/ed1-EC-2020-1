#include "Task.h"

/* 
    Allocates memory for the new task 
    being created and init default values 
*/
Task_t* createTask(char* title, char* description){
    if(strlen(title) >= TASK_DISPLAY_WIDTH)
        return NULL;


    // aloca memória 
    Task_t* new_task = (Task_t*) malloc(sizeof(Task_t));
    if(!new_task) return NULL;


    // atribui os valores 
    setDescription(new_task, description);
    setTitle(new_task, title);

    new_task->numb_labels = 0;

    // init labels
    for(int i = 0; i < LABELS_MAX; i++)
        new_task->labels[i] = NULL;
    

    for(int i = 0; i < NUMB_COLORS; i++)
        new_task->available_colors[i] = TRUE;

    new_task->win = NULL;


    return new_task;
}




int deleteTask(Task_t* t){
    if(!t) return ERR;

    if(isDisplayed(t)) hide(t);
  
    free(t);
    return OK;
}




int addLabel(Task_t* t, Label_t* label){
    if(!t || !label || t->numb_labels >= LABELS_MAX || !t->available_colors[label->color]) 
        return ERR;

    t->available_colors[label->color] = FALSE;
    t->labels[t->numb_labels++] = label;
}



int removeLabel(Task_t* t, LabelName label_name){

    for(int i = 0; i < t->numb_labels; i++)
    {
        if(!strcmp(t->labels[i]->name, label_name)) 
        {
            // deletes the label found
            deleteLabel(t->labels[i]);
            t->labels[i] = NULL;

            // re-orders the sequencial list
            for(int i = 0; i < LABELS_MAX - 1; i++)
                t->labels[i] = t->labels[i + 1];

            t->numb_labels--;

            return OK; 
        }
        
    }

    return ERR;

}



int moveTask(Task_t* t, int y, int x, bool select){
    if(!t || !isDisplayed(t))
        return ERR;

    hide(t); 
    show(t, y, x, select);
}




int show(Task_t* t, unsigned int y, unsigned x, bool selected){

    if(!t) return ERR; 
    if(!t->win || IS_RESIZED) t->win = newwin(TASK_DISPLAY_HEIGHT, TASK_DISPLAY_WIDTH, y, x);    

    refresh();

    box(t->win, 0, 0); // desenha a borda da janela

    int title_len = strlen(t->title);


    // move to the center up of the component and print the title
    if(selected)
       wattron(t->win, A_REVERSE);

    mvwprintw(t->win, 0, (TASK_DISPLAY_WIDTH - title_len)/2, "%s", t->title);
    wattroff(t->win, A_REVERSE);


    // display the labels if there are any 
    if(t->numb_labels)
    {
        for(int i = 0; i < t->numb_labels && i < TASK_DISPLAY_HEIGHT - 2; i++)
        {
            Color label_color = t->labels[i]->color;

            wmove(t->win, 1 + i, 1);


            // if the color pair has already beeing init and it is init again
            // it causes a segmentation fault (core dumped) error
            if(!INIT_PAIRS[label_color])
            {
                init_pair(label_color, COLOR_BLACK, label_color);
                INIT_PAIRS[label_color] = TRUE;
            }


            // toggles the color attribute 
            wattron(t->win, COLOR_PAIR(label_color));
            wprintw(t->win, "%s",t->labels[i]->name);
            wattroff(t->win, COLOR_PAIR(label_color));
        }


        // in case there are more labels but not enough space we display "..."
        if(t->numb_labels >= TASK_DISPLAY_HEIGHT - 2)
                wprintw(t->win, "%s", " ...");
    }

    wrefresh(t->win);
}



int hide(Task_t* t){
    if(!t || !isDisplayed(t)) return ERR; 

    eraseWin(t->win, TASK_DISPLAY_HEIGHT, TASK_DISPLAY_WIDTH);

    t->win = NULL;
}





bool isDisplayed(Task_t* t){
    return t->win ? TRUE : FALSE;
}




int setDescription(Task_t* t, char* d){
    if(!t || strlen(d) >= DESCRIPTION_SIZE) return ERR;

    strcpy(t->description, d);

    return OK;
}




int setTitle(Task_t* t, char* title){
    if(!t || strlen(title) >= TASK_DISPLAY_WIDTH) return ERR;

    strcpy(t->title, title);

    return OK;
}




char* getDescription(Task_t* t){
    return !t ? (char*) ERR : t->description;
}




char* getTitle(Task_t* t){
    return !t ? (char* ) ERR : t->title;
}




