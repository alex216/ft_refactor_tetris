/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proceed_update_score_and_map.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:24 by yliu              #+#    #+#             */
/*   Updated: 2024/01/29 10:07:06 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static	bool	_check_a_line_is_filled(const char table[COL])
{
	int	sum = 0;

	for (int x = 0; x < COL; x++)
			sum += table[x];
	return (sum == COL);
}

static void	_remap_table_above_y(const int max_row, char table[ROW][COL])
{
	for (int i = max_row; i >= 1; i--)
		for (int j = 0; j < COL; j++)
			table[i][j] = table[i - 1][j];
	for (int j = 0; j < COL; j++)
		table[0][j] = 0;
}

static void	_revise_game_info(t_game_clock *const clock, int *const score)
{
	clock->interval_time -= clock->decrease_ms--;
	*score += 100 * COL;
}

static void _proceed_remap_and_revise_info(t_game_info *const info)
{
	for (int y = 0; y < ROW; y++)
	{
		if (_check_a_line_is_filled(info->map_table[y]))
		{
			_remap_table_above_y(y, info->map_table);
			_revise_game_info(&(info->clock), &info->score);
		}
	}
}

void	proceed_update_score_and_map(t_game_info *const info)
{
	stick_block_to_map(info->current_block, &info->map_table);
	_proceed_remap_and_revise_info(info);
	respawn_block(&info->current_block);
	set_is_game_continue(info->current_block, &info->is_game_continue, info->map_table);
}
