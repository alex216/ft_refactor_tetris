/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:33 by yliu              #+#    #+#             */
/*   Updated: 2024/01/08 16:12:42 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static void	_initialize_game(t_game_info *info)
{
	info->final_score = 0;
	info->timer = STARTING_TIME;
	info->GameOn = true;
	info->decrease = DEFAULT_DECREASE_SPEED;
	gettimeofday(&(info->before_now), NULL);
}

static t_bool	_check_if_has_to_update(t_game_info *info)
{
	suseconds_t current_time = info->now.tv_sec * INTERVAL_MS + info->now.tv_usec;
	suseconds_t previous_time = info->before_now.tv_sec * INTERVAL_MS + info->before_now.tv_usec;

	return (current_time - previous_time > info->timer);
}

static void	_process_tetris(t_game_info *info)
{
	char pressed_key;

	// set the length of time getch() waits for input
	timeout(1);
	while (info->GameOn)
	{
		if ((pressed_key = getch()) != ERR)
		{
			control_key_press(pressed_key, info);
			print_screen(info->final_score);
		}
		gettimeofday(&(info->now), NULL);
		if (_check_if_has_to_update(info))
		{
			control_key_press(DOWN_KEY, info);
			print_screen(info->final_score);
			gettimeofday(&(info->before_now), NULL);
		}
	}
}

static void	_display_result(int final_score)
{
	for (int x = 0; x < ROW_MAX; x++)
	{
		for (int y = 0; y < COL_MAX; y++)
			printf("%c ", Table[x][y] ? BLOCK_CHAR : BLANK_CHAR);
		printf("\n");
	}
	printf("\nGame over!\n\nScore: %d\n", final_score);
}

int	main(void)
{
	t_game_info info;

	_initialize_game(&info);
	srand(time(0));
	initscr();

	check_game_then_refresh_g_current(&info);
	print_screen(info.final_score);
	_process_tetris(&info);

	destruct_shape(g_current);
	endwin();
	_display_result(info.final_score);

	return (0);
}
