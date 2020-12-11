#include "utils.h"

bool isNullPointer(void* ptr){ 
    return !ptr ? TRUE : FALSE; 
}

bool equals(char* str1, char* str2){
    return !strcmp(str1, str2) ? TRUE : FALSE; 
}

bool errorIn(int err) {
    return err == ERR;
}