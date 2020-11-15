#ifndef __PROJECTORG_H__
#define __PROJECTORG_H__

/* Global definitions, functions and var */
#include <ncurses.h>

#include <stdlib.h>
#include <string.h>
#include <Label.h>

#define ERROR -1
#define SUCCESS 0

// tamanhos máximos
#define TITLE_SIZE 256
#define DESCRIPTION_SIZE 1024
#define NAME_SIZE 64
#define EMAIL_SIZE 64

// char* com os tamanhos específicos de title e description
typedef char Description[DESCRIPTION_SIZE];
typedef char Title[TITLE_SIZE]; 
typedef char Name[NAME_SIZE]; 
typedef char Email[EMAIL_SIZE]; 




#endif 