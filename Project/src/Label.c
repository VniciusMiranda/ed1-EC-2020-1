#include "Label.h"

Label_t* createLabel(Color color, LabelName name){
    if(color >= NUMB_COLORS || strlen(name) > LABEL_NAME_SIZE)
        return NULL; 

    Label_t* new_label = (Label_t*) malloc(sizeof(Label_t));
    if(!new_label) return NULL;

    if(!isColorInit(color)) initColor(color);

    setLabelColor(new_label, color);
    setLabelName(new_label, name);

    return new_label;
}

int deleteLabel(Label_t* l){
    if(!l) return ERR;

    free(l);
    return OK;
}

int copyLabel(Label_t* dest, Label_t* src) {
    if(isNullPointer(src) || isNullPointer(dest)) return ERR;

    dest->color = src->color;
    strcpy(dest->name, src->name);
    return OK;
}

int setLabelColor(Label_t* l, Color c){
    if(c >= NUMB_COLORS) return ERR;
        l->color = c;
        return OK;
}

int setLabelName(Label_t* l, LabelName name){
    if(strlen(name) > LABEL_NAME_SIZE) return ERR;
        strcpy(l->name, name);
        return OK;
}

Color getLabelColor(Label_t* l){
    return l ? l->color : (Color) ERR;
}

char* getLabelName(Label_t* l){
    return l ? l->name :  (char*) ERR;
}

