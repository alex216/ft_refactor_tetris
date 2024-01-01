#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>

#define COL_MAX 15
#define ROW_MAX 20

typedef struct
{
	char	**array;
	int		width;
	int		row;
	int		col;
}			Struct;

// main
int			main(void);
Struct		FunctionCS(Struct shape);
void		FunctionDS(Struct shape);
int			FunctionCP(Struct shape);
void		FunctionRS(Struct shape);
void		print_screen(void);
int			hasToUpdate(void);

// utils
void		set_timeout(int time);
