/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proceed_update_score_and_map.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:24 by yliu              #+#    #+#             */
/*   Updated: 2024/01/21 01:03:47 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static void	_remap_table_above_y(const int max_row, char table[ROW_MAX][COL_MAX])
{
	for (int i = max_row; i >= 1; i--)
		for (int j = 0; j < COL_MAX; j++)
			table[i][j] = table[i - 1][j];
	for (int j = 0; j < COL_MAX; j++)
		table[0][j] = 0;
}

static	bool	_check_a_line_is_filled(const char table[COL_MAX])
{
	int	sum = 0;

	for (int x = 0; x < COL_MAX; x++)
			sum += table[x];
	return (sum == COL_MAX);
}

static void	_revise_game_info(t_game_clock *const clock, int *const final_score)
{
	clock->interval_time -= clock->decrease_ms--;
	*final_score += 100 * COL_MAX;
}

static void _proceed_remap_and_revise_info(t_game_info *const info)
{
	for (int y = 0; y < ROW_MAX; y++)
	{
		if (_check_a_line_is_filled(info->map_table[y]))
		{
			_remap_table_above_y(y, info->map_table);
			_revise_game_info(&(info->clock), &info->final_score);
		}
	}
}

void	proceed_update_score_and_map(t_game_info *const info)
{
	stick_shape_to_map(info->current_shape, &info->map_table);
	_proceed_remap_and_revise_info(info);
	respawn_shape(&info->current_shape);
	set_to_is_game_continue(info->current_shape, &(info->is_game_continue), info->map_table);
}
