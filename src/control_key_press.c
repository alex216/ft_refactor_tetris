/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_key_press.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:28 by yliu              #+#    #+#             */
/*   Updated: 2024/01/06 15:56:38 by kaksano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

// move down
void	_move_down(t_shape temp, t_game_info *info)
{
	temp.row++;
	if (check_shape_with_map(temp, info))
		g_current.row++;
	else
		proceed_update_score_and_map(info);
}

// move shape to right
static void	_move_right(t_shape temp, t_game_info *info)
{
    temp.col++;
    if (check_shape_with_map(temp, info))
        g_current.col++;
}

// move shape to left
static void _move_left(t_shape temp, t_game_info *info)
{
    temp.col--;
    if (check_shape_with_map(temp, info))
        g_current.col--;
}

// rotate shape clockwise
static void _move_rotate(t_shape temp, t_game_info *info)
{
    rotate_shape(temp);
    if (check_shape_with_map(temp, info))
        rotate_shape(g_current);
}

// switch according to key input using function pointer
void control_key_press(const char c, t_game_info *info, t_shape temp)
{
	int	index = -1;
	const switch_keypress_behaviour keyFunctions[] = {
		_move_down,
		_move_right,
		_move_left,
		_move_rotate
	};

    switch (c) {
        case 's': index = 0; break;
        case 'd': index = 1; break;
        case 'a': index = 2; break;
        case 'w': index = 3; break;
		default : break;
    }
    if (index != -1)
        keyFunctions[index](temp, info);
}
