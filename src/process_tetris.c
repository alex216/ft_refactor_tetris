/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tetris.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 22:02:08 by yliu              #+#    #+#             */
/*   Updated: 2024/01/29 10:27:21 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static t_bool	_check_if_has_to_update(t_game_clock clock)
{
	suseconds_t current_time; 
	suseconds_t previous_time;

	current_time = clock.now.tv_sec * INTERVAL_MS + clock.now.tv_usec;
	previous_time = clock.before_now.tv_sec * INTERVAL_MS + clock.before_now.tv_usec;

	return (current_time - previous_time > clock.interval_time);
}

void	process_tetris(t_game_info *info)
{
	char pressed_key;

	// set the length of time getch() waits for input
	timeout(1);

	while (info->is_game_continue)
	{
		if ((pressed_key = getch()) != ERR)
		{
			control_key_press(pressed_key, info);
		}
		gettimeofday(&(info->clock.now), NULL);
		if (_check_if_has_to_update(info->clock))
		{
			gettimeofday(&(info->clock.before_now), NULL);
			control_key_press(DOWN_KEY, info);
		}
		print_screen(info->current_block, info->score, info->map_table);
	}
}
