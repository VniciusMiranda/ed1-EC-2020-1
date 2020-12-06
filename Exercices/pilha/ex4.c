#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define True 1
#define False 0


typedef struct elemento{
    char c[20];
    struct elemento* prox;

} Elemento_t;

typedef Elemento_t* Pilha_t;
typedef int bool;

Pilha_t p = NULL;

int restart(Pilha_t* p);

int push(Pilha_t* p, char* c);

//char* pop(Pilha_t* p);
int pop(Pilha_t* p);

char* top(Pilha_t p);

bool is_empty(Pilha_t* p);


int main(){

    char direction[20], street[20];
    char s[20];

    int t;

    scanf("%d", &t);

    while(t--)
    {

        push(&p, "CASA");

        while(True)
        {
            scanf("%s", s);

            if(!strcmp("ESCOLA", s)) break;
            push(&p, s);
        }

        while(!is_empty(&p))
        {
            strcpy(direction, !strcmp(top(p), "DIREITA") ? "ESQUERDA" : "DIREITA");
            pop(&p);

            strcpy(street, top(p));
            pop(&p);


            if(!strcmp(street, "CASA"))
                printf("Vire a %s na sua %s.\n", direction, street);

            else
                printf("Vire a %s na rua %s.\n", direction, street);

        }
    }


    return 0;
}


int restart(Pilha_t* p){
    char* c;

    do{
        c = pop(p);

    }while(c);

    return 1;
}


int push(Pilha_t* p, char* c){

    Elemento_t* novo_elemento = (Elemento_t*) malloc(sizeof(Elemento_t));
    if(!novo_elemento) return -1;


    strcpy(novo_elemento->c, c);
    novo_elemento->prox = *p;

    *p = novo_elemento;


    return 1;
}


bool is_empty(Pilha_t* p){ return !(*p); }


/*char* pop(Pilha_t* p){
    if(!*p) return '\0';

    // top element
    Elemento_t* top = *p;
    char* c;
    strcpy(c, top->c);
    *p = top->prox;
    free(top);

    return c;
}*/


int pop(Pilha_t* p){
    if(!*p) return -1;

    // top element
    Elemento_t* top = *p;
    //char* c;
    //strcpy(c, top->c);
    *p = top->prox;
    free(top);

    return 1;
}


char* top(Pilha_t p){
    return p->c;
}
