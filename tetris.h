#ifndef TETRIS_H
# define TETRIS_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>

// game settings
#define COL_MAX 15
#define ROW_MAX 20
#define BLOCK_CHAR '#'
#define BLANK_CHAR '.'
#define ROTATE_CLOCKWISE true

#define NUMBER_OF_TOTAL_SHAPES (sizeof(g_StructsArray) / sizeof(g_StructsArray[0]))
#define IS_CELL_OCCUPIED (array[i][j])
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

typedef struct shape
{
	char	**array;
	int		width;
	int		row;
	int		col;
}			t_shape;

// Function prototypes
typedef void (*switch_keypress_behaviour)(t_shape *, t_game_info *, t_shape *, int *);

// global variable
extern const t_shape	g_StructsArray[7];
extern char				Table[ROW_MAX][COL_MAX];
extern struct timeval	before_now, now;
extern t_shape			g_current;

// main.c
int		main(void);
void	refresh_g_current_then_game_on(t_game_info *, t_shape *);

// utils.c
void	initiate_game(t_game_info *);
int		hasToUpdate(t_game_info *);
void	print_screen(t_game_info *);
void	display_result(t_game_info *);
t_shape	create_shape(void);

// cmds_for_shape.c
int		check_shape(t_shape, t_game_info *);
t_shape	copy_shape(t_shape);
void	rotate_shape(t_shape);
void	destruct_shape(t_shape);

// handle_key_press.c
void	handle_key_press(char, t_game_info *, t_shape *, int *, t_shape *);

#endif // TETRIS_H
