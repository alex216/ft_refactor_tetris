/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:41 by yliu              #+#    #+#             */
/*   Updated: 2024/01/19 22:35:55 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

void	refresh_g_current(void)
{
	const t_shape	new_shape = create_shape();

	destruct_shape(g_current);
	g_current = new_shape;
}

void	check_game_on_with_g_current(bool *GameOn, char table[ROW_MAX][COL_MAX])
{
		*GameOn = check_shape_with_map(g_current, table);
}

void	copy_g_current_shape_to_map(char (*table)[ROW_MAX][COL_MAX])
{
	for (int i = 0; i < g_current.width; i++)
		for (int j = 0; j < g_current.width; j++)
			if (g_current.array[i][j])
				(*table)[g_current.row + i][g_current.col
					+ j] = g_current.array[i][j];
}

void	print_screen(int final_score, char table[ROW_MAX][COL_MAX])
{
	char	buffer[ROW_MAX][COL_MAX] = {0};
	char	*title = "42 Tetris";

	copy_g_current_shape_to_map(&buffer);

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
