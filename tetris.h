#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>

#define COL_MAX 15
#define ROW_MAX 20
#define BLOCK_CHAR '#'
#define BLANK_CHAR '.'


typedef struct game_info
{
	int				final_score; 
	suseconds_t		timer;
	char			GameOn;
	int				decrease;
// char			Table[ROW_MAX][COL_MAX] = {0};
	// char			Table[ROW_MAX][COL_MAX];
	// void		*Table;
}	t_game_info;

typedef struct
{
	char	**array;
	int		width;
	int		row;
	int		col;
}			Struct;

// global variable
extern const Struct	StructsArray[7];
extern char			Table[ROW_MAX][COL_MAX];

// main
int			main(void);
void		FunctionDS(Struct shape);
int			FunctionCP(Struct shape);
void		print_screen(void);
int			hasToUpdate(void);

// utils
void		set_timeout(int time);
void		rotate_shape(Struct shape);
Struct		copy_shape(Struct shape);
