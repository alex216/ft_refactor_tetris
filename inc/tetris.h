/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:18 by yliu              #+#    #+#             */
/*   Updated: 2024/01/21 01:05:49 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define COL_MAX 15
#define ROW_MAX 20
#define LEFT_KEY 'a'
#define RIGHT_KEY 'd'
#define ROTATE_KEY 'w'
#define DOWN_KEY 's'
#define BLOCK_CHAR '#'
#define BLANK_CHAR '.'
#define ROTATE_CLOCKWISE true
#define DEFAULT_DECREASE_SPEED 1000
#define STARTING_TIME 400000
#define INTERVAL_MS 1000000
#define NUMBER_OF_TOTAL_SHAPES 7
#define IS_CELL_OCCUPIED (array[i][j])
#define IS_TABLE_OCCUPIED (table[shape.row + i][shape.col + j])
#define IS_OUTSIDE_BOUNDS \
	(									\
		shape.col + j < 0 			|| 	\
		shape.col + j >= COL_MAX	||	\
		shape.row + i >= ROW_MAX		\
	)

typedef int t_bool;

typedef struct shape
{
	char	**array;
	int		width;
	int		row;
	int		col;
}			t_shape;

typedef struct	s_game_clock
{
	suseconds_t		interval_time;
	int				decrease_ms;
	struct timeval	before_now;
	struct timeval	now;
}					t_game_clock;

typedef struct game_info
{
	int				final_score; 
	bool			is_game_continue;
	t_game_clock	clock;
	char			map_table[ROW_MAX][COL_MAX];
	t_shape			current_shape;
}					t_game_info;

typedef struct s_key_action_dictionary
{
	const char	pressed_key;
	void		(*key_action_function)(t_shape, t_game_info *);
}				t_key_action_dictionary;

extern const t_shape	g_structs_array[NUMBER_OF_TOTAL_SHAPES];

int		main(void);

void	process_tetris(t_game_info *);

void	control_key_press(const char pressed_key, t_game_info *);

void	proceed_update_score_and_map(t_game_info *const);

t_shape	create_shape(void);
t_shape	copy_shape(const t_shape);
void	rotate_shape(const t_shape);
void	destruct_shape(const t_shape);

bool	check_map_for_gamecontinue(const t_shape, const char table[ROW_MAX][COL_MAX]);
void	set_to_is_game_continue(const t_shape, bool *const GameOn,const char table[ROW_MAX][COL_MAX]);
void	stick_shape_to_map(const t_shape, char (*const table)[ROW_MAX][COL_MAX]);
void	print_screen(const t_shape, const int final_score, const char table[ROW_MAX][COL_MAX]);
void	respawn_shape(t_shape *);

#endif
