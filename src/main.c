/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:33 by yliu              #+#    #+#             */
/*   Updated: 2024/01/20 23:59:07 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static void	_initialize_game(t_game_info *info, int argc, char **argv)
{
	int	i = 0;

	info->final_score = 0;
	info->is_game_continue = true;
	info->current_shape = create_shape();
	info->clock.interval_time = STARTING_TIME;
	info->clock.decrease_ms = DEFAULT_DECREASE_SPEED;
	gettimeofday(&info->clock.before_now, NULL);
	if (argc == 2)
		while (argv[1][i])
			i++;
	info->is_color = (i == 2 && argv[1][0] == '-' && argv[1][1] == 'c');
	for (int x = 0; x < ROW_MAX; x++)
	{
		for (int y = 0; y < COL_MAX; y++)
		{
			info->map_table[x][y][0] = 0;
			info->map_table[x][y][1] = 0;
		}
	}
}

static void	_display_result(int final_score, char (table)[ROW_MAX][COL_MAX][2])
{
	for (int x = 0; x < ROW_MAX; x++)
	{
		for (int y = 0; y < COL_MAX; y++)
			printf("%c ", table[x][y][0] ? BLOCK_CHAR : BLANK_CHAR);
		printf("\n");
	}
	printf("\nGame over!\n\nScore: %d\n", final_score);
}

int	main(int argc, char **argv)
{
	t_game_info info;

	_initialize_game(&info, argc, argv);
	srand(time(0));
	initscr();
	if (info.is_color)
	{
		start_color();
	}

	respawn_shape(&info.current_shape);
	set_bool_to_is_game_continue(info.current_shape, &info.is_game_continue, info.map_table);
	print_screen(info.is_color, info.current_shape, info.final_score, info.map_table);

	process_tetris(&info);

	destruct_shape(info.current_shape);
	endwin();
	_display_result(info.final_score, info.map_table);

	return (0);
}
