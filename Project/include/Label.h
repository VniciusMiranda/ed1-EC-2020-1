#ifndef __LABEL_H__
#define __LABEL_H__ 

#include "Display.h"

#define LABEL_NAME_SIZE 20

typedef char LabelName[LABEL_NAME_SIZE];

typedef struct Label{ 
    LabelName name;
    Color color;

} Label_t;

Label_t* createLabel(Color color, LabelName name);

int deleteLabel(Label_t* l);

int setLabelColor(Label_t* l, Color c);

int setLabelName(Label_t* l, LabelName name);

Color getLabelColor(Label_t* l);

char* getLabelName(Label_t* l);

#endif