/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_key_press.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:28 by yliu              #+#    #+#             */
/*   Updated: 2024/01/23 15:01:49 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static void	_move_down(t_block temp, t_game_info *info)
{
	temp.row++;
	if (check_map_for_gamecontinue(temp, info->map_table))
		info->current_block.row++;
	else
		proceed_update_score_and_map(info);
}

static void	_move_right(t_block temp, t_game_info *info)
{
    temp.col++;
    if (check_map_for_gamecontinue(temp, info->map_table))
        info->current_block.col++;
}

static void _move_left(t_block temp, t_game_info *info)
{
    temp.col--;
    if (check_map_for_gamecontinue(temp, info->map_table))
        info->current_block.col--;
}

static void _move_rotate(t_block temp, t_game_info *info)
{
    rotate_block(temp);
    if (check_map_for_gamecontinue(temp, info->map_table))
        rotate_block(info->current_block);
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
			t_block block_under_control = copy_block(info->current_block);
			key_action[i].key_action_function(block_under_control, info);
			destruct_block(block_under_control);
		}
	}
}
