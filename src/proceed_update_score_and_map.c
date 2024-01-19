/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proceed_update_score_and_map.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:24 by yliu              #+#    #+#             */
/*   Updated: 2024/01/19 22:38:15 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static void	_remap_table(const int max_row, char table[ROW_MAX][COL_MAX])
{
	for (int i = max_row; i >= 1; i--)
		for (int j = 0; j < COL_MAX; j++)
			table[i][j] = table[i - 1][j];
	for (int j = 0; j < COL_MAX; j++)
		table[0][j] = 0;
}

static void _count_vanish_line_then_add_score(t_game_info *info)
{
	int sum, count;

	count = 0;
	for (int n = 0; n < ROW_MAX; n++)
	{
		sum = 0;
		for (int m = 0; m < COL_MAX; m++)
			sum += info->Table[n][m];
		if (sum == COL_MAX)
		{
			count++;
			_remap_table(n, info->Table);
			info->clock.interval_time -= info->clock.decrease_ms--;
		}
	}
	info->final_score += 100 * count * COL_MAX;
}

void	proceed_update_score_and_map(t_game_info *info)
{
	copy_g_current_shape_to_map(&info->Table);
	_count_vanish_line_then_add_score(info);
	refresh_g_current();
	check_game_on_with_g_current(&(info->GameOn), info->Table);
}
