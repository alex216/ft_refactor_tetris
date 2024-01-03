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

	for (i = 0; i < current.width; i++)
	{
		for (j = 0; j < current.width; j++)
			if (current.array[i][j])
				Buffer[current.row + i][current.col + j] = current.array[i][j];
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

void	press_s_key(Struct *temp, t_game_info *info, Struct *new_shape, int *count)
{
	int i, j, n, m, sum;

	temp->row++;
	if (check_shape(*temp, info))
		current.row++;
	else
	{
		for (i = 0; i < current.width; i++)
		{
			for (j = 0; j < current.width; j++)
			{
				if (current.array[i][j])
					Table[current.row + i][current.col + j] = current.array[i][j];
			}
		}
		*count = 0;
		for (n = 0; n < ROW_MAX; n++)
		{
			sum = 0;
			for (m = 0; m < COL_MAX; m++)
				sum += Table[n][m];
			if (sum == COL_MAX)
			{
				(*count)++;
				int l, k;
				for (k = n; k >= 1; k--)
					for (l = 0; l < COL_MAX; l++)
						Table[k][l] = Table[k - 1][l];
				for (l = 0; l < COL_MAX; l++)
					Table[k][l] = 0;
				info->timer -= info->decrease--;
			}
		}
		// count line
		info->final_score += 100 * *count;
		*new_shape = copy_shape(StructsArray[rand() % 7]);
		new_shape->col = rand() % (COL_MAX - new_shape->width + 1);
		new_shape->row = 0;
		destruct_shape(current);
		current = *new_shape;
		if (!check_shape(current, info))
		{
			info->GameOn = false;
		}
	}
}
