#include "tetris.h"
#include <stdbool.h>

static void	_move_right(t_shape *temp, t_game_info *info, t_shape *new_shape, int *count);
static void _move_left(t_shape *temp, t_game_info *info, t_shape *new_shape, int *count);
static void _rotate(t_shape *temp, t_game_info *info, t_shape *new_shape, int *count);
static void	_move_down(t_shape *temp, t_game_info *info, t_shape *new_shape, int *count);
static void _check_if_any_line(t_game_info *info, t_shape *new_shape, int *count);
void handle_key_press(char c, t_game_info *info, t_shape *new_shape, int *count, t_shape *temp);

// move shape to right
static void	_move_right(t_shape *temp, t_game_info *info, t_shape *new_shape, int *count)
{
    temp->col++;
    if (check_shape(*temp, info))
        g_current.col++;
}

// move shape to left
static void _move_left(t_shape *temp, t_game_info *info, t_shape *new_shape, int *count)
{
    temp->col--;
    if (check_shape(*temp, info))
        g_current.col--;
}

// rotate shape clockwise
static void _rotate(t_shape *temp, t_game_info *info, t_shape *new_shape, int *count)
{
    rotate_shape(*temp);
    if (check_shape(*temp, info))
        rotate_shape(g_current);
}

// move down
static void	_move_down(t_shape *temp, t_game_info *info, t_shape *new_shape, int *count)
{
	temp->row++;
	if (check_shape(*temp, info) == true)
		g_current.row++;
	else
		_check_if_any_line(info, new_shape, count);
}

// check if newly added shape shapes line
static void _check_if_any_line(t_game_info *info, t_shape *new_shape, int *count)
{
	int i, j, n, m, sum;

	// copy g_current to Table
	for (i = 0; i < g_current.width; i++)
		for (j = 0; j < g_current.width; j++)
			if (g_current.array[i][j])
				Table[g_current.row + i][g_current.col + j] = g_current.array[i][j];
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
	info->final_score += 100 * *count; // add to final score
	*new_shape = create_shape();
	destruct_shape(g_current);
	g_current = *new_shape;
	if (check_shape(g_current, info) == false)
	{
		info->GameOn = false;
	}
}

// switch according to key input using function pointer
void handle_key_press(char c, t_game_info *info, t_shape *new_shape, int *count, t_shape *temp)
{
	int	index = -1;

    switch (c) {
        case 's': index = 0; break;
        case 'd': index = 1; break;
        case 'a': index = 2; break;
        case 'w': index = 3; break;
		default : break;
    }
	switch_keypress_behaviour keyFunctions[] = {
		_move_down,
		_move_right,
		_move_left,
		_rotate
	};
    if (index != -1)
        keyFunctions[index](temp, info, new_shape, count);
}
