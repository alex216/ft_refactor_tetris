/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:41 by yliu              #+#    #+#             */
/*   Updated: 2024/01/29 10:11:16 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

bool	static _is_outside_of_border(const t_block block, int i, int j)
{
	return (block.col + j < 0 || block.col + j >= COL || block.row + i >= ROW);
}

bool	check_map_for_continue(
								const t_block block,
								const char map[ROW][COL])
{
	const char	**array = (const char **)block.array;

	for (int i = 0; i < block.width; i++)
		for (int j = 0; j < block.width; j++)
			if (array[i][j]
				&& (_is_outside_of_border(block , i , j) 
					|| map[block.row + i][block.col + j]))
				return (false);
	return (true);
}

void	set_is_game_continue(
						const t_block block,
						bool *is_game_continue,
						const char map[ROW][COL])
{
		*is_game_continue = check_map_for_continue(block, map);
}

void	stick_block_to_map(
							const t_block block,
							char (*map)[ROW][COL])
{
	for (int i = 0; i < block.width; i++)
		for (int j = 0; j < block.width; j++)
			if (block.array[i][j])
				(*map)[block.row + i][block.col + j] = block.array[i][j];
}

void	print_screen(
					const t_block block,
					const int score,
					const char map[ROW][COL])
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
			printw("%c ", (map[i][j] || buffer[i][j]) ? BLOCK_CHAR : BLANK_CHAR);
		printw("\n");
	}

	printw("\nScore: %d\n", score);
}
