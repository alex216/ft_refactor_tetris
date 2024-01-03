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
extern struct timeval	before_now, now;
extern Struct			current;

// main
int			main(void);
void		initiate_game(t_game_info *p);
void		print_screen(t_game_info *p);
int			hasToUpdate(t_game_info *p);

// utils
void		display_result(t_game_info *p);
void		destruct_shape(Struct shape);
void		press_s_key(Struct *temp, t_game_info *info, Struct *new_shape, int *count);

// cmd_shape
void		rotate_shape(Struct shape);
Struct		copy_shape(Struct shape);
int			check_shape(Struct shape, t_game_info *p);
