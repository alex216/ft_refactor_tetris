/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:18 by yliu              #+#    #+#             */
/*   Updated: 2024/01/06 18:21:17 by kaksano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO:	global_variables
// TODO:	break down game_info struct			yliu
// TODO:	function pointer					yliu

// TODO:	refresh_g_current make it together
// TODO:	change the name KeyFunction
// TODO:	delete useless comments
// TODO:	write better algorithm of _count_vanish_line_then_add_score

#ifndef TETRIS_H
#define TETRIS_H

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
#define DEFAULT_DECREASE_SPEED 1000
#define STARTING_TIME 400000
#define INTERVAL_MICROSECONDS 1000000

// macro for readability
#define NUMBER_OF_TOTAL_SHAPES (sizeof(g_StructsArray) / sizeof(g_StructsArray[0]))
#define IS_CELL_OCCUPIED (array[i][j])
#define IS_TABLE_OCCUPIED (Table[shape.row + i][shape.col + j])
#define IS_OUTSIDE_BOUNDS \
	(\
		shape.col + j < 0 || \
		shape.col + j >= COL_MAX || \
		shape.row + i >= ROW_MAX\
	)

typedef int t_bool;

typedef struct game_info
{
	int				final_score; 
	suseconds_t		timer;
	bool			GameOn;
	int				decrease;
	struct timeval	before_now, now;
}	t_game_info;

typedef struct shape
{
	char	**array;
	int		width;
	int		row;
	int		col;
}			t_shape;

// Function prototypes
typedef void (*switch_keypress_behaviour)(t_shape , t_game_info *);

// global variable
extern const t_shape	g_StructsArray[7];
extern char				Table[ROW_MAX][COL_MAX];
extern t_shape			g_current;

// main.c
int		main(void);

// utils.c
void	refresh_g_current(t_game_info *);
void	check_game_on_with_g_current(t_game_info *);
void	copy_g_current_shape_to_map(char (*)[ROW_MAX][COL_MAX]);

// control_key_press.c
void	control_key_press(const char, t_game_info *, t_shape);

// proceed_update_score_and_map.c
void	proceed_update_score_and_map(t_game_info *);

// cmds_for_shape.c
t_shape	create_shape(void);
int		check_shape_with_map(const t_shape, const t_game_info *);
t_shape	copy_shape(const t_shape);
void	rotate_shape(const t_shape);
void	destruct_shape(const t_shape);

#endif // TETRIS_H
