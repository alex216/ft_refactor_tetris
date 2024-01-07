/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:33 by yliu              #+#    #+#             */
/*   Updated: 2024/01/06 16:24:03 by kaksano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static void	_initialize_game(t_game_info *info)
{
	info->final_score = 0;
	info->clock.interval_time = STARTING_TIME;
	info->GameOn = true;
	info->clock.decrease_ms = DEFAULT_DECREASE_SPEED;
	gettimeofday(&(info->clock.before_now), NULL);
}

// checks if it is time to update the game state based on a timer
static t_bool	_check_if_has_to_update(t_game_clock game_clock)
{
	suseconds_t current_time = game_clock.now.tv_sec * INTERVAL_MICROSECONDS + game_clock.now.tv_usec;
	suseconds_t previous_time = game_clock.before_now.tv_sec * INTERVAL_MICROSECONDS + game_clock.before_now.tv_usec;

	return (current_time - previous_time > game_clock.interval_time);
}

// copy shape to Buffer, then print both Table and Buffer
static void	_print_screen(int final_score)
{
	char	Buffer[ROW_MAX][COL_MAX] = {0};

	// copy g_current to Buffer
	copy_g_current_shape_to_map(&Buffer);

	// clear screen, print game title
	clear();
	for (int i = 0; i < COL_MAX - 9; i++)
		printw(" ");
	printw("42 Tetris\n");

	// display block and blank by adding Table and Buffer
	for (int i = 0; i < ROW_MAX; i++)
	{
		for (int j = 0; j < COL_MAX; j++)
			printw("%c ", (Table[i][j] + Buffer[i][j]) ? BLOCK_CHAR : BLANK_CHAR);
		printw("\n");
	}

	// display current score
	printw("\nScore: %d\n", final_score);
}

// copy_shape, handle_key_input, free shape, then print
static void _manage_frame(const char c, t_game_info *info)
{
	t_shape temp = copy_shape(g_current);

	control_key_press(c, info, temp);
	destruct_shape(temp);
	_print_screen(info->final_score);
}

static bool	_is_valid_key_pressed(const char key)
{
	return (key == 'w' || key == 'a' || key == 's' || key == 'd');
}

// process main tetris program
static void	_process_tetris(t_game_info *info)
{
	char c;

	// set the length of time getch() waits for input
	timeout(1);
	while (info->GameOn)
	{
		// check key input is valid
		if ((c = getch()) != ERR && _is_valid_key_pressed(c))
			_manage_frame(c, info);
		// check time to update no matter key input
		gettimeofday(&(info->clock.now), NULL);
		if (_check_if_has_to_update(info->clock))
		{
			_manage_frame('s', info);
			gettimeofday(&(info->clock.before_now), NULL);
		}
	}
}

// display result
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

	// initialize
	_initialize_game(&info);
	srand(time(0));
	initscr();

	// exec game unless GameOn is false during executing _manage_a_frame
	refresh_g_current();
	check_game_on_with_g_current(&(info.GameOn));
	_print_screen(info.final_score);
	_process_tetris(&info);

	// finish program
	destruct_shape(g_current);
	endwin();
	_display_result(info.final_score);

	return (0);
}
