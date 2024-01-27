/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:33 by yliu              #+#    #+#             */
/*   Updated: 2024/01/27 14:00:48 by kaksano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static void	_initialize_game(t_game_info *info)
{
	info->score = 0;
	info->is_game_end = false;
	info->clock.interval_time = STARTING_TIME;
	info->clock.decrease_ms= DEFAULT_DECREASE_SPEED;
	gettimeofday(&info->clock.before_now, NULL);
	for (int x = 0; x < ROW; x++)
		for (int y = 0; y < COL; y++)
			info->map_table[x][y] = 0;
	info->current_block = create_block();
}

static void	_display_result(
							const int score,
							const char (map)[ROW][COL])
{
	for (int x = 0; x < ROW; x++)
	{
		for (int y = 0; y < COL; y++)
			printf("%c ", map[x][y] ? BLOCK_CHAR : BLANK_CHAR);
		printf("\n");
	}
	printf("\nGame over!\n\nScore: %d\n", score);
}

int	main(void)
{
	t_game_info info;

	_initialize_game(&info);
	srand(time(0));
	initscr();

	print_screen(info.current_block, info.score, info.map_table);
	set_is_game_end(info.current_block, &info.is_game_end, info.map_table);

	process_tetris(&info);

	destruct_block(info.current_block);
	endwin();
	_display_result(info.score, info.map_table);

	return (0);
}
