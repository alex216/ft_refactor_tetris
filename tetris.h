#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define F 0
#define T 1
#define C 15
#define R 20

typedef struct
{
	char	**array;
	int		width, row, col;
}			Struct;

// main
int			main(void);
Struct		FunctionCS(Struct shape);
void		FunctionDS(Struct shape);
int			FunctionCP(Struct shape);
void		FunctionRS(Struct shape);
void		FunctionPT(void);
int			hasToUpdate(void);

// utils
void		set_timeout(int time);
