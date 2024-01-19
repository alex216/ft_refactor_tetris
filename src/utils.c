/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:41 by yliu              #+#    #+#             */
/*   Updated: 2024/01/08 15:59:37 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

void	refresh_g_current()
{
	const t_shape	new_shape = create_shape();

	destruct_shape(g_current);
	g_current = new_shape;
}

void	check_game_on_with_g_current(t_game_info *info)
{
	info->GameOn = check_shape_with_map(g_current, info);
}

void	check_game_then_refresh_g_current(t_game_info *info)
{
	refresh_g_current();
	check_game_on_with_g_current(info);
}

void	copy_g_current_shape_to_map(char (*table)[ROW_MAX][COL_MAX])
{
	for (int i = 0; i < g_current.width; i++)
		for (int j = 0; j < g_current.width; j++)
			if (g_current.array[i][j])
				(*table)[g_current.row + i][g_current.col
					+ j] = g_current.array[i][j];
}

void	print_screen(int final_score)
{
	char	Buffer[ROW_MAX][COL_MAX] = {0};

	copy_g_current_shape_to_map(&Buffer);

	clear();
	for (int i = 0; i < COL_MAX - 9; i++)
		printw(" ");
	printw("42 Tetris\n");

	for (int i = 0; i < ROW_MAX; i++)
	{
		for (int j = 0; j < COL_MAX; j++)
			printw("%c ", (Table[i][j] + Buffer[i][j]) ? BLOCK_CHAR : BLANK_CHAR);
		printw("\n");
	}

	printw("\nScore: %d\n", final_score);
}
