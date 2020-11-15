#include "Label.h"


Label_t* createLabel(Color color, LabelName name){

    if(color >= NUMB_COLORS || strlen(name) > LABEL_NAME_SIZE)
        return NULL; 


    Label_t* new_label = (Label_t*) malloc(sizeof(Label_t));

    if(!new_label) return NULL;


    if(!INIT_PAIRS[color])
        init_pair(color, color, COLOR_BLACK);


    setColor(new_label, color);
    setLabelName(new_label, name);


    return new_label;
}




int deleteLabel(Label_t* l){
    if(!l) return ERR;

    free(l);
    return OK;
}





// _______setters__________


int setColor(Label_t* l, Color c){
    if(c >= NUMB_COLORS) return ERR;

        l->color = c;
        return OK;
}




int setLabelName(Label_t* l, LabelName name){
    if(strlen(name) > LABEL_NAME_SIZE) return ERR;

        strcpy(l->name, name);
        return OK;
}




// _______gettters________

Color getColor(Label_t* l){
    return l ? l->color : (Color) ERR;
}




char* getLabelName(Label_t* l){

    return l ? l->name :  (char*) ERR;

}

