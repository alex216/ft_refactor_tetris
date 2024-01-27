/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:18 by yliu              #+#    #+#             */
/*   Updated: 2024/01/27 13:58:06 by kaksano          ###   ########.fr       */
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

#define COL 15
#define ROW 20
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
#define TYPES_OF_BLOCKS 7
#define IS_CELL_OCCUPIED (array[i][j])
#define IS_TABLE_OCCUPIED (map[block.row + i][block.col + j])
#define IS_OUTSIDE_BOUNDS			\
	(								\
		block.col + j < 0		||	\
		block.col + j >= COL	||	\
		block.row + i >= ROW)

typedef int t_bool;

typedef struct s_block
{
	char **array;
	int width;
	int row;
	int col;
} t_block;

typedef struct s_game_clock
{
	suseconds_t interval_time;
	int decrease_ms;
	struct timeval before_now;
	struct timeval now;
} t_game_clock;

typedef struct s_game_info
{
	int score;
	bool is_game_end;
	t_game_clock clock;
	char map_table[ROW][COL];
	t_block current_block;
} t_game_info;

typedef struct s_key_action_dictionary
{
	const char pressed_key;
	void (*key_action_function)(t_block, t_game_info *);
} t_key_action_dictionary;

extern const t_block g_structs_array[TYPES_OF_BLOCKS];

int	main(void);

void	process_tetris(t_game_info *);

void	control_key_press(const char pressed_key, t_game_info *);

void	proceed_update_score_and_map(t_game_info *const);

t_block	copy_block(const t_block);
t_block	create_block(void);
void	respawn_block(t_block *);
void	rotate_block(const t_block);
void	destruct_block(const t_block);

bool	check_map_for_continue(const t_block, const char map[ROW][COL]);
void	set_is_game_end(const t_block, bool *is_game_end, const char map[ROW][COL]);
void	stick_block_to_map(const t_block, char (*map)[ROW][COL]);
void	print_screen(const t_block, const int score, const char map[ROW][COL]);

#endif
