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

bool INIT_PAIRS[NUMB_COLORS];
bool IS_RESIZED;

int PREV_Y, PREV_X; 

typedef struct PrintBannerArgs{
    int y;
    int x;
    bool* stop;
} PrintBannerArgs;

typedef unsigned int Color;

void initColors();

void initColorsIds();

void initColor(Color color);

bool isColorInit(Color color);

/* this function runs as a thread, so the args need to be passed this way */
void* printBanner(void* args);

int selectWin(char** options, char* question, int num_options, int y, int x, unsigned int width, unsigned int height, int default_choice);

int inputWin(char* question, int y, int x, unsigned int width, unsigned int height, char* answer);

int infoWin(char* text, int y, int x, unsigned int width, unsigned int height);

int eraseWin(WINDOW* w, int height, int width);

void printWithColor(WINDOW* win, Color color, char* str);

void printWithAttribute(WINDOW* win, int attr, char* str);

int mainMenu(int* err);

void createProjectScreen();

int projectScreen();

#endif 