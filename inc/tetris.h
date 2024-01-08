/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:18 by yliu              #+#    #+#             */
/*   Updated: 2024/01/07 22:21:13 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO:	global_variables

#ifndef TETRIS_H
#define TETRIS_H

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
#define ROTATE_CLOCKWISE true
#define DEFAULT_DECREASE_SPEED 1000
#define STARTING_TIME 400000
#define INTERVAL_MICROSECONDS 1000000
#define NUMBER_OF_TOTAL_SHAPES 7
#define IS_CELL_OCCUPIED (array[i][j])
#define IS_TABLE_OCCUPIED (Table[shape.row + i][shape.col + j])
#define IS_OUTSIDE_BOUNDS \
	(									\
		shape.col + j < 0 			|| 	\
		shape.col + j >= COL_MAX	||	\
		shape.row + i >= ROW_MAX		\
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

typedef struct s_key_action_dictionary
{
	const char	pressed_key;
	void		(*key_action_function)(t_shape, t_game_info *);
}				t_key_action_dictionary;

extern const t_shape	g_StructsArray[NUMBER_OF_TOTAL_SHAPES];
extern char				Table[ROW_MAX][COL_MAX];
extern t_shape			g_current;

int		main(void);

void	refresh_g_current(void);
void	check_game_on_with_g_current(t_game_info *);
void	check_game_then_refresh_g_current(t_game_info *info);
void	copy_g_current_shape_to_map(char (*)[ROW_MAX][COL_MAX]);

void	control_key_press(const char pressed_key, t_game_info *, t_shape);

void	proceed_update_score_and_map(t_game_info *);

t_shape	create_shape(void);
int		check_shape_with_map(const t_shape, const t_game_info *);
t_shape	copy_shape(const t_shape);
void	rotate_shape(const t_shape);
void	destruct_shape(const t_shape);

#endif
