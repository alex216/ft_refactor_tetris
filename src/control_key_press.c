/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_key_press.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:28 by yliu              #+#    #+#             */
/*   Updated: 2024/01/07 22:22:04 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

void	_move_down(t_shape temp, t_game_info *info)
{
	temp.row++;
	if (check_shape_with_map(temp, info))
		g_current.row++;
	else
		proceed_update_score_and_map(info);
}

static void	_move_right(t_shape temp, t_game_info *info)
{
    temp.col++;
    if (check_shape_with_map(temp, info))
        g_current.col++;
}

static void _move_left(t_shape temp, t_game_info *info)
{
    temp.col--;
    if (check_shape_with_map(temp, info))
        g_current.col--;
}

static void _move_rotate(t_shape temp, t_game_info *info)
{
    rotate_shape(temp);
    if (check_shape_with_map(temp, info))
        rotate_shape(g_current);
}

void control_key_press(const char pressed_key, t_game_info *info, t_shape shape_under_control)
{
	static const t_key_action_dictionary	key_action[] = {
		{'d', _move_right},
		{'a', _move_left},
		{'w', _move_rotate},
		{'s', _move_down}
	};

	int i = 0;
	while (i < sizeof(key_action) / sizeof(key_action[0]))
	{
		if (key_action[i].pressed_key == pressed_key)
		{
			key_action[i].key_action_function(shape_under_control, info);
			break;
		}
		i++;
	}
}
