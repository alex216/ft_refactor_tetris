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

#define IS_CELL_OCCUPIED (array[i][j])
// #define IS_TABLE_OCCUPIED (info->Table[shape.row + i][shape.col + j])
#define IS_TABLE_OCCUPIED (Table[shape.row + i][shape.col + j])
#define IS_OUTSIDE_BOUNDS \
	(\
		shape.col + j < 0 || \
		shape.col + j >= COL_MAX || \
		shape.row + i >= ROW_MAX\
	)

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
void		initiate_game(t_game_info *p);
int			validate_shape_move(Struct shape, t_game_info *p);
void		print_screen(t_game_info *p);
int			hasToUpdate(t_game_info *p);

// utils
void		rotate_shape(Struct shape);
Struct		copy_shape(Struct shape);
void		display_result(t_game_info *p);
void		destruct_shape(Struct shape);
