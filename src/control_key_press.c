/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_key_press.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:28 by yliu              #+#    #+#             */
/*   Updated: 2024/01/20 23:58:59 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static void	_move_down(t_shape temp, t_game_info *info)
{
	temp.row++;
	if (check_map_for_gamecontinue(temp, info->map_table))
		info->current_shape.row++;
	else
		proceed_update_score_and_map(info);
}

static void	_move_right(t_shape temp, t_game_info *info)
{
    temp.col++;
    if (check_map_for_gamecontinue(temp, info->map_table))
        info->current_shape.col++;
}

static void _move_left(t_shape temp, t_game_info *info)
{
    temp.col--;
    if (check_map_for_gamecontinue(temp, info->map_table))
        info->current_shape.col--;
}

static void _move_rotate(t_shape temp, t_game_info *info)
{
    rotate_shape(temp);
    if (check_map_for_gamecontinue(temp, info->map_table))
        rotate_shape(info->current_shape);
}

void control_key_press(const char pressed_key, t_game_info *info)
{
	static const t_key_action_dictionary	key_action[] = {
		{RIGHT_KEY, _move_right},
		{LEFT_KEY, _move_left},
		{ROTATE_KEY, _move_rotate},
		{DOWN_KEY, _move_down}
	};

	for (int i = 0; i < sizeof(key_action) / sizeof(key_action[0]); i++)
	{
		if (key_action[i].pressed_key == pressed_key)
		{
			t_shape shape_under_control = copy_shape(info->current_shape);
			key_action[i].key_action_function(shape_under_control, info);
			destruct_shape(shape_under_control);
		}
	}
}
