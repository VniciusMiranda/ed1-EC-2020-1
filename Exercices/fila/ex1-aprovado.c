#include <stdio.h>
#include <stdlib.h>

#define ERR -1
#define OK 0
#define CRITICAL_PACIENT 1

#define TRUE 1
#define FALSE 0


typedef int bool;

typedef struct Time {
    int hour;
    int minute;

} Time_t;

Time_t* createTime(int hour, int min);

int increment_time_min( Time_t * t, int m );

int time_in_min(Time_t* t);

int setTime(Time_t* t, int h, int m);

Time_t* copyTime(Time_t* src);

typedef struct Pacient{

    int critical_time; 
    Time_t arrived;  
    struct Pacient* next;

} Pacient_t;

// pacients p
typedef struct Pacients { 

    Pacient_t * begining;
    Pacient_t * end;
    
    int size;

} Pacients_t;


Pacients_t* createPacients();

int insertPacient(Pacients_t* p, int h, int m, int c);

int attendPacient(Pacients_t* p, Time_t * attendTime);

int destroyPacients(Pacients_t* p);



int main(){


    Time_t attendance_time;
    Pacients_t* sus = createPacients();

    int n, i = 0;
    int min, hour, critical_time, critical_pacients = 0;

    scanf("%d", &n);

    setTime(&attendance_time, 7, 0); 

    while(n--)
    {
        scanf("%d %d %d", &hour, &min, &critical_time);

        // paciente chega
        insertPacient(sus, hour, min, critical_time);

        // se o paciente chega e não há ninguem sendo atendido
        if(time_in_min(&attendance_time) < hour*60 + min)
        {

            // pacientes só são atendidos em meias horas ou horas inteiras
            if(min < 30 && min != 0)
                setTime(&attendance_time, hour, 30);
            
            else if(min > 30)
                setTime(&attendance_time, ++hour, 0);
        } 

        // paciente é atendido
        if(attendPacient(sus, &attendance_time) == CRITICAL_PACIENT)
            critical_pacients++;
        
        increment_time_min(&attendance_time, 30);
    }

    printf("%d", critical_pacients);

    return OK;
}


Pacients_t* createPacients(){
    Pacients_t * p = (Pacients_t*) malloc(sizeof(Pacients_t));

    p->begining = NULL;
    p->end = p->begining;
    p->size = 0;

    return p; 
    
}


int insertPacient(Pacients_t* p, int h, int m, int c){

    Pacient_t * new_pacient = (Pacient_t*) malloc(sizeof(Pacient_t));
    if(!new_pacient) return ERR;

    new_pacient->arrived.hour = h;
    new_pacient->arrived.minute = m;
    new_pacient->critical_time = c;

    if(!p->begining) 
        p->begining = new_pacient;
    else
        p->end->next = new_pacient;

    p->end = new_pacient;

    return OK;

}

// if cretical time was reached before being attended return ERR
int attendPacient(Pacients_t* p, Time_t* attendTime){

    Pacient_t * remove = p->begining; 

    int critical_time = remove->critical_time;
    Time_t* arrived = copyTime(&remove->arrived);

    p->begining = p->begining->next;

    free(remove);
    if(!p->begining) p->end = NULL; 

    int time_waiting = time_in_min(attendTime) - time_in_min(arrived);

    return time_waiting > critical_time ? CRITICAL_PACIENT : OK;
}


int destroyPacients(Pacients_t* p){
    Pacient_t *remove, *end = p->begining;

    while(end)
    {
        remove = end;
        end = end->next;
        free(remove);
    }

    p->end = NULL;
    p->begining = NULL;

    return OK;
}


Time_t* createTime(int hour, int min){
    Time_t* new_time = (Time_t*) malloc(sizeof(Time_t));

    new_time->hour = hour;
    new_time->minute = min;
}

int setTime(Time_t* t, int h, int m){
    if(!t) return ERR;

    t->hour = h;
    t->minute = m;

    return OK;
}


int increment_time_min(Time_t * t, int m){
    t->minute += m;

    if(t->minute >= 60)
    {
        t->hour++;
        t->minute = t->minute - 60; 
    }

}


int time_in_min(Time_t* t){
    return t->hour*60 + t->minute; 
}

Time_t* copyTime(Time_t* src){
    Time_t* dest = (Time_t*) malloc(sizeof(Time_t));

    dest->hour = src->hour;
    dest->minute = src->minute;

    return dest;
}