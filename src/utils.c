/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:41 by yliu              #+#    #+#             */
/*   Updated: 2024/01/23 15:01:49 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

bool	check_map_for_gamecontinue(
									const t_block block,
									const char table[ROW][COL])
{
	const char	**array = (const char **)block.array;

	for (int i = 0; i < block.width; i++)
		for (int j = 0; j < block.width; j++)
			if (IS_CELL_OCCUPIED && (IS_OUTSIDE_BOUNDS
				|| IS_TABLE_OCCUPIED))
				return (false);
	return (true);
}

void	set_to_is_game_continue(
								const t_block block,
								bool *const is_game_continue,
								const char table[ROW][COL])
{
		*is_game_continue = check_map_for_gamecontinue(block, table);
}

void	stick_block_to_map(
							const t_block block,
							char (*const table)[ROW][COL])
{
	for (int i = 0; i < block.width; i++)
		for (int j = 0; j < block.width; j++)
			if (block.array[i][j])
				(*table)[block.row + i][block.col + j] = block.array[i][j];
}

void	print_screen(
					const t_block block,
					const int score,
					const char table[ROW][COL])
{
	char	buffer[ROW][COL] = {0};
	static char	title[10] = "42 Tetris\0";

	stick_block_to_map(block, &buffer);

	clear();
	for (int i = 0; i < COL - (int)strlen(title); i++)
		printw(" ");
	printw("%s\n", title);

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
			printw("%c ", (table[i][j] + buffer[i][j]) ? BLOCK_CHAR : BLANK_CHAR);
		printw("\n");
	}

	printw("\nScore: %d\n", score);
}
