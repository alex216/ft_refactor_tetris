/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proceed_update_score_and_map.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:24 by yliu              #+#    #+#             */
/*   Updated: 2024/01/07 20:38:19 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

void	_remap_table(const int max_row)
{
	for (int i = max_row; i >= 1; i--)
		for (int j = 0; j < COL_MAX; j++)
			Table[i][j] = Table[i - 1][j];
	for (int j = 0; j < COL_MAX; j++)
		Table[0][j] = 0;
}

static void _count_vanish_line_then_add_score(t_game_info *info)
{
	int sum, count;

	count = 0;
	for (int n = 0; n < ROW_MAX; n++)
	{
		sum = 0;
		for (int m = 0; m < COL_MAX; m++)
			sum += Table[n][m];
		if (sum == COL_MAX)
		{
			count++;
			_remap_table(n);
			info->timer -= info->decrease--;
		}
	}
	info->final_score += 100 * count * COL_MAX;
}

void	proceed_update_score_and_map(t_game_info *info)
{
	copy_g_current_shape_to_map(&Table);
	_count_vanish_line_then_add_score(info);
	check_game_then_refresh_g_current(info);
}
