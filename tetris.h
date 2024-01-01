#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>

typedef struct {
    char **array;
    int width, row, col;
} Struct;

// main
int main();
Struct FunctionCS(Struct shape);
void FunctionDS(Struct shape);
int FunctionCP(Struct shape);
void FunctionRS(Struct shape);
void FunctionPT();
int hasToUpdate();

// utils
void set_timeout(int time);
