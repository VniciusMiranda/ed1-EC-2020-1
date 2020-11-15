#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <ncurses.h>

#include <string.h>
#include <stdlib.h>

#include <pthread.h>
#include <unistd.h>

#define DIS_CONV_FACTOR 3.7
#define NUMB_COLORS 8

pthread_t banner_th;

int INIT_PAIRS[NUMB_COLORS];
bool IS_RESIZED;

int PREV_Y, PREV_X; 


typedef struct PrintBannerArgs{
    int y;
    int x;
    bool* stop;
} PrintBannerArgs;


void init_colors();

/* this function runs as a thread, so the args need to be passed this way */
void* printBanner(void* args);


/* creates a display context in the display on the given position with the options passed.
   the context is destroyed when the option is selected */
int selectWin(char** options, char* question, int num_options, int y, int x, unsigned int width, unsigned int height, int default_choice);

int inputWin(char* question, int y, int x, unsigned int width, unsigned int height, char* answer);

int infoWin(char* text, int y, int x, unsigned int width, unsigned int height);

int eraseWin(WINDOW* w, int height, int width);

int main_menu(int* err);

int loop(int* err);

#endif 