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

static void	_initialize_game(t_game_info *info)
{
	info->final_score = 0;
	info->is_game_continue = true;
	info->current_shape = create_shape();
	info->clock.interval_time = STARTING_TIME;
	info->clock.decrease_ms = DEFAULT_DECREASE_SPEED;
	gettimeofday(&info->clock.before_now, NULL);
	for (int x = 0; x < ROW_MAX; x++)
		for (int y = 0; y < COL_MAX; y++)
			info->Table[x][y] = 0;
	info->current_shape = create_shape();
}

static void	_display_result(int final_score, char (table)[ROW_MAX][COL_MAX])
{
	for (int x = 0; x < ROW_MAX; x++)
	{
		for (int y = 0; y < COL_MAX; y++)
			printf("%c ", table[x][y] ? BLOCK_CHAR : BLANK_CHAR);
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

	print_screen(info.current_shape, info.final_score, info.Table);
	respawn_shape(&info.current_shape);
	set_bool_to_is_game_continue(info.current_shape, &info.is_game_continue, info.map_table);

	process_tetris(&info);

	destruct_shape(info.current_shape);
	endwin();
	_display_result(info.final_score, info.map_table);

	return (0);
}
