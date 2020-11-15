#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 30

#define ERR -1
#define OK 0



typedef struct Child {

    int number;
    char name[MAX_NAME_SIZE];
    struct Child * next;
    struct Child * prev;

} Child_t;


typedef struct Circle {

    Child_t * head; 
    int size;

} Circle_t;


int insertChild(Circle_t* circle, char* name, unsigned int number);

int removeClockwise(Circle_t* circle, unsigned int index, Child_t* removed_child);

int removeAntiClockwise(Circle_t* circle, unsigned int index, Child_t* removed_child);

int circleCount(Circle_t* circle, Child_t* removed_child); 

Circle_t* createCircle();


int main(){

    Circle_t* circle = createCircle();

    int n;
    scanf("%d", &n);

    int number;
    char name[MAX_NAME_SIZE];

    while(n--)
    {
        scanf("%s %d", name, &number);
        insertChild(circle, name, number);
    }

    Child_t winner;

    if(circleCount(circle, &winner) == ERR) return ERR;
    
    printf("%s", winner.name);

    return OK;
}


Circle_t* createCircle(){
    Circle_t* new_circle = (Circle_t*) malloc(sizeof(Circle_t));
    if(!new_circle) return NULL;


    new_circle->head = NULL;
    new_circle->size = 0;

    return new_circle;
}


int insertChild(Circle_t* circle, char* name, unsigned int number){
    if(!circle) return ERR;

    if(number < 1 || number > 500) return ERR;

    if(strlen(name) > MAX_NAME_SIZE) return ERR;

    Child_t* new_child = (Child_t*) malloc(sizeof(Child_t));
    if(!new_child) return ERR;

    strcpy(new_child->name, name);
    new_child->number = number;  

    if(!circle->head) 
    {
        new_child->next = new_child;
        new_child->prev = new_child; 
        circle->head = new_child;
    }
    else
    {
        new_child->next = circle->head;
        new_child->prev = circle->head->prev;
        new_child->prev->next = new_child;

        circle->head->prev = new_child;
    }

    circle->size++;

    return OK;
}


int childCopy(Child_t* dest, Child_t* src){

    strcpy(dest->name, src->name);
    dest->number = src->number;
    dest->next = src->next;
    dest->prev = src->prev;

}


int removeClockwise(Circle_t* circle, unsigned int index, Child_t* removed_child){
    int i = 0;

    Child_t* aux = circle->head;

    while(i++ < index) aux = aux->prev;

    childCopy(removed_child, aux);

    if(aux == circle->head)
        circle->head = aux->next;
    
    aux->next->prev = aux->prev;
    aux->prev->next = aux->next;

    free(aux);

    circle->size--;

    return OK;
}

int removeAntiClockwise(Circle_t* circle, unsigned int index, Child_t* removed_child){
    int i = 0;

    Child_t* aux = circle->head;


    while(i++ < index) aux = aux->next;

    childCopy(removed_child, aux);

    if(aux == circle->head)
        circle->head = aux->next;
        
    aux->next->prev = aux->prev;

    aux->prev->next = aux->next;

    free(aux);

    circle->size--;

    return OK;
}

int circleCount(Circle_t* circle, Child_t* winner){ 
    if(!circle || !winner) return ERR; 

    int status;
    int head_number = circle->head->number; 
    Child_t removed_child;

    while(circle->size > 1)
    {

        status = head_number % 2 == 0 ? 
            removeClockwise(circle, head_number, &removed_child) :
            removeAntiClockwise(circle, head_number, &removed_child);
        
        head_number = removed_child.number;
    }

    childCopy(winner, circle->head);

    return status;

    
}
