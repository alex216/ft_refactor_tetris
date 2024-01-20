/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:41 by yliu              #+#    #+#             */
/*   Updated: 2024/01/21 00:04:32 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

void	respawn_shape(t_shape *shape)
{
	const t_shape	new_shape = create_shape();

	destruct_shape(*shape);
	*shape = new_shape;

}

bool	check_map_for_gamecontinue(const t_shape shape, char table[ROW_MAX][COL_MAX][2])
{
	const char	**array = (const char **)shape.array;

	for (int i = 0; i < shape.width; i++)
		for (int j = 0; j < shape.width; j++)
			if (IS_CELL_OCCUPIED && (IS_OUTSIDE_BOUNDS || IS_TABLE_OCCUPIED))
				return (false);
	return (true);
}

void	set_bool_to_is_game_continue(t_shape shape, bool *is_game_continue, char table[ROW_MAX][COL_MAX][2])
{
		*is_game_continue = check_map_for_gamecontinue(shape, table);
}

void	stick_shape_to_map(t_shape shape, char (*table)[ROW_MAX][COL_MAX][2])
{
	for (int i = 0; i < shape.width; i++)
	{
		for (int j = 0; j < shape.width; j++)
		{
			if (shape.array[i][j])
			{
				(*table)[shape.row + i][shape.col
					+ j][0] = shape.array[i][j];
				(*table)[shape.row + i][shape.col
					+ j][1] = shape.number + 1;
			}
		}
	}
}

static void _set_color(char buf, int tab_shape_index, t_shape shape)
{
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_YELLOW, COLOR_BLACK);
	init_pair(8, COLOR_WHITE, COLOR_BLACK);
	if (buf)
		attron(COLOR_PAIR(shape.number + 1));
	else if (tab_shape_index)
		attron(COLOR_PAIR(tab_shape_index));
	else
		attron(COLOR_PAIR(8));
}

static void	_print_a_char(bool color, char buf, char table_one, int tab_shape_index, t_shape shape)
{
	if (color)
		_set_color(buf, tab_shape_index, shape);
	printw("%c ", (table_one + buf) ? BLOCK_CHAR : BLANK_CHAR);
	if (color)
		attron(COLOR_PAIR(8));
}

void	print_screen(bool color, t_shape shape, int final_score, char table[ROW_MAX][COL_MAX][2])
{
	char	buffer[ROW_MAX][COL_MAX][2] = {0};
	static char	title[10] = "42 Tetris\0";

	stick_shape_to_map(shape, &buffer);

	clear();
	for (int i = 0; i < COL_MAX - (int)strlen(title); i++)
		printw(" ");
	printw("%s\n", title);

	for (int i = 0; i < ROW_MAX; i++)
	{
		for (int j = 0; j < COL_MAX; j++)
			_print_a_char(color, buffer[i][j][0], table[i][j][0], table[i][j][1], shape);
		printw("\n");
	}

	printw("\nScore: %d\n", final_score);
}
