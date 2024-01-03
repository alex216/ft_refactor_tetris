#include "tetris.h"

// initialize t_game_info struct variable
void	initiate_game(t_game_info *info)
{
	info->final_score = 0;
	info->timer = 400000;
	info->GameOn = true;
	info->decrease = 1000;
}

// display result
void	display_result(t_game_info *info)
{
	int x, y;
	for (x = 0; x < ROW_MAX; x++)
	{
		for (y = 0; y < COL_MAX; y++)
			printf("%c ", Table[x][y] ? BLOCK_CHAR : BLANK_CHAR);
		printf("\n");
	}
	printf("\nGame over!\n\nScore: %d\n", info->final_score);
}

int	hasToUpdate(t_game_info *info)
{
	suseconds_t current_time;
	suseconds_t previous_time;

	current_time = now.tv_sec * 1000000 + now.tv_usec;
	previous_time = before_now.tv_sec * 1000000 + before_now.tv_usec;
	if (current_time - previous_time > info->timer)
		return (true);
	else
		return (false);
}

void	print_screen(t_game_info *info)
{
	char	Buffer[ROW_MAX][COL_MAX] = {0};
	int i, j;

	for (i = 0; i < g_current.width; i++)
	{
		for (j = 0; j < g_current.width; j++)
			if (g_current.array[i][j])
				Buffer[g_current.row + i][g_current.col + j] = g_current.array[i][j];
	}
	clear();
	for (i = 0; i < COL_MAX - 9; i++)
		printw(" ");
	printw("42 Tetris\n");
	for (i = 0; i < ROW_MAX; i++)
	{
		for (j = 0; j < COL_MAX; j++)
			printw("%c ", (Table[i][j] + Buffer[i][j]) ? BLOCK_CHAR : BLANK_CHAR);
		printw("\n");
	}
	printw("\nScore: %d\n", info->final_score);
}
