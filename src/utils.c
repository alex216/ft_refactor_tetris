/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:41 by yliu              #+#    #+#             */
/*   Updated: 2024/01/05 13:37:42 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/tetris.h"

void	refresh_g_current_then_check_game_on(t_game_info *info);
void	copy_g_current_shape_to_map(char (*table)[ROW_MAX][COL_MAX]);

void	refresh_g_current_then_check_game_on(t_game_info *info)
{
	// refresh g current
	const t_shape	new_shape = create_shape();
	destruct_shape(g_current);
	g_current = new_shape;

	// check whether game may continue
	if (check_shape_with_map(g_current, info) == false)
		info->GameOn = false;
}

void	copy_g_current_shape_to_map(char (*table)[ROW_MAX][COL_MAX])
{
	for (int i = 0; i < g_current.width; i++)
		for (int j = 0; j < g_current.width; j++)
			if (g_current.array[i][j])
				(*table)[g_current.row + i][g_current.col + j] = g_current.array[i][j];
}
