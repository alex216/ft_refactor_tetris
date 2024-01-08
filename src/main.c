/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:33 by yliu              #+#    #+#             */
/*   Updated: 2024/01/07 22:22:26 by yliu             ###   ########.fr       */
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
	suseconds_t current_time = info->now.tv_sec * INTERVAL_MICROSECONDS + info->now.tv_usec;
	suseconds_t previous_time = info->before_now.tv_sec * INTERVAL_MICROSECONDS + info->before_now.tv_usec;

	return (current_time - previous_time > info->timer);
}

static void	_print_screen(t_game_info *info)
{
	char	Buffer[ROW_MAX][COL_MAX] = {0};

	copy_g_current_shape_to_map(&Buffer);

	clear();
	for (int i = 0; i < COL_MAX - 9; i++)
		printw(" ");
	printw("42 Tetris\n");

	for (int i = 0; i < ROW_MAX; i++)
	{
		for (int j = 0; j < COL_MAX; j++)
			printw("%c ", (Table[i][j] + Buffer[i][j]) ? BLOCK_CHAR : BLANK_CHAR);
		printw("\n");
	}

	printw("\nScore: %d\n", info->final_score);
}

static void _manage_frame(const char pressed_key, t_game_info *info)
{
	t_shape shape_under_control = copy_shape(g_current);

	control_key_press(pressed_key, info, shape_under_control);
	destruct_shape(shape_under_control);
	_print_screen(info);
}

static bool	_is_valid_key_pressed(const char key)
{
	return (key == 'w' || key == 'a' || key == 's' || key == 'd');
}

static void	_process_tetris(t_game_info *info)
{
	char c;

	// set the length of time getch() waits for input
	timeout(1);
	while (info->GameOn)
	{
		if ((c = getch()) != ERR && _is_valid_key_pressed(c))
			_manage_frame(c, info);

		gettimeofday(&(info->now), NULL);
		if (_check_if_has_to_update(info))
		{
			_manage_frame('s', info);
			gettimeofday(&(info->before_now), NULL);
		}
	}
}

static void	_display_result(t_game_info *info)
{
	for (int x = 0; x < ROW_MAX; x++)
	{
		for (int y = 0; y < COL_MAX; y++)
			printf("%c ", Table[x][y] ? BLOCK_CHAR : BLANK_CHAR);
		printf("\n");
	}
	printf("\nGame over!\n\nScore: %d\n", info->final_score);
}

int	main(void)
{
	t_game_info info;

	_initialize_game(&info);
	srand(time(0));
	initscr();

	check_game_then_refresh_g_current(&info);
	_print_screen(&info);
	_process_tetris(&info);

	destruct_shape(g_current);
	endwin();
	_display_result(&info);

	return (0);
}
