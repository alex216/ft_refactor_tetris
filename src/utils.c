/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:41 by yliu              #+#    #+#             */
/*   Updated: 2024/01/23 13:20:49 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

bool	check_map_for_gamecontinue(
									const t_shape shape,
									const char table[ROW_MAX][COL_MAX])
{
	const char	**array = (const char **)shape.array;

	for (int i = 0; i < shape.width; i++)
		for (int j = 0; j < shape.width; j++)
			if (IS_CELL_OCCUPIED && (IS_OUTSIDE_BOUNDS
				|| IS_TABLE_OCCUPIED))
				return (false);
	return (true);
}

void	set_to_is_game_continue(
								const t_shape shape,
								bool *const is_game_continue,
								const char table[ROW_MAX][COL_MAX])
{
		*is_game_continue = check_map_for_gamecontinue(shape, table);
}

void	stick_shape_to_map(
							const t_shape shape,
							char (*const table)[ROW_MAX][COL_MAX])
{
	for (int i = 0; i < shape.width; i++)
		for (int j = 0; j < shape.width; j++)
			if (shape.array[i][j])
				(*table)[shape.row + i][shape.col + j] = shape.array[i][j];
}

void	print_screen(
					const t_shape shape,
					const int final_score,
					const char table[ROW_MAX][COL_MAX])
{
	char	buffer[ROW_MAX][COL_MAX] = {0};
	static char	title[10] = "42 Tetris\0";

	stick_shape_to_map(shape, &buffer);

	clear();
	for (int i = 0; i < COL_MAX - (int)strlen(title); i++)
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
