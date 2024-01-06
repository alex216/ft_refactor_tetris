/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proceed_update_score_and_map.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:24 by yliu              #+#    #+#             */
/*   Updated: 2024/01/06 15:53:09 by kaksano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/tetris.h"

// remap from above
void	_remap_table(const int max_row)
{
	// remap above line n of Table[][]
	for (int i = max_row; i >= 1; i--)
		for (int j = 0; j < COL_MAX; j++)
			Table[i][j] = Table[i - 1][j];
	// fill zero at the top line
	for (int j = 0; j < COL_MAX; j++)
		Table[0][j] = 0;
}

// count tetris vanish line
static void _count_vanish_line_then_add_score(t_game_info *info)
{
	int sum, count;

	count = 0;
	// remap Table[][] one line after another from top line
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
	refresh_g_current(info);
	check_game_on_with_g_current(info);
}
