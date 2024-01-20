/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:41 by yliu              #+#    #+#             */
/*   Updated: 2024/01/20 10:58:50 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

void	refresh_current_shape(t_shape *shape)
{
	const t_shape	new_shape = create_shape();

	destruct_shape(*shape);
	*shape = new_shape;

}

bool	check_map_for_gamecontinue(const t_shape shape, char table[ROW_MAX][COL_MAX])
{
	const char	**array = (const char **)shape.array;

	for (int i = 0; i < shape.width; i++)
		for (int j = 0; j < shape.width; j++)
			if (IS_CELL_OCCUPIED && (IS_OUTSIDE_BOUNDS || IS_TABLE_OCCUPIED))
				return (false);
	return (true);
}

void	set_bool_to_GameOn_if_gameover(t_shape g_current, bool *is_game_over, char table[ROW_MAX][COL_MAX])
{
		*is_game_over = check_map_for_gamecontinue(g_current, table);
}

void	copy_g_current_shape_to_map(t_shape g_current, char (*table)[ROW_MAX][COL_MAX])
{
	for (int i = 0; i < g_current.width; i++)
		for (int j = 0; j < g_current.width; j++)
			if (g_current.array[i][j])
				(*table)[g_current.row + i][g_current.col
					+ j] = g_current.array[i][j];
}

void	print_screen(t_shape g_current, int final_score, char table[ROW_MAX][COL_MAX])
{
	char	buffer[ROW_MAX][COL_MAX] = {0};
	char	*title = "42 Tetris";

	copy_g_current_shape_to_map(g_current, &buffer);

	clear();
	for (int i = 0; i < COL_MAX - strlen(title); i++)
		printw(" ");
	printw("%s\n", title);

	for (int i = 0; i < ROW_MAX; i++)
	{
		for (int j = 0; j < COL_MAX; j++)
			printw("%c ", (table[i][j] + buffer[i][j]) ? BLOCK_CHAR : BLANK_CHAR);
		printw("\n");
	}

	printw("\nScore: %d\n", final_score);
}
