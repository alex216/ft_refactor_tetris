#include "tetris.h"
#include <stdbool.h>

static void	_move_right(t_shape temp, t_game_info *info);
static void _move_left(t_shape temp, t_game_info *info);
static void _rotate(t_shape temp, t_game_info *info);
static void	_move_down(t_shape temp, t_game_info *info);
static void _check_if_any_line(t_game_info *info);
void 		handle_key_press(const char c, t_game_info *info, t_shape temp);

// move shape to right
static void	_move_right(t_shape temp, t_game_info *info)
{
    temp.col++;
    if (check_shape(temp, info))
        g_current.col++;
}

// move shape to left
static void _move_left(t_shape temp, t_game_info *info)
{
    temp.col--;
    if (check_shape(temp, info))
        g_current.col--;
}

// rotate shape clockwise
static void _rotate(t_shape temp, t_game_info *info)
{
    rotate_shape(temp);
    if (check_shape(temp, info))
        rotate_shape(g_current);
}

// move down
static void	_move_down(t_shape temp, t_game_info *info)
{
	temp.row++;
	if (check_shape(temp, info) == true)
		g_current.row++;
	else
		_check_if_any_line(info);
}

// check if newly added shape shapes line
static void _check_if_any_line(t_game_info *info)
{
	int n, m, sum, count;

	// copy g_current to Table
	for (int i = 0; i < g_current.width; i++)
		for (int j = 0; j < g_current.width; j++)
			if (g_current.array[i][j])
				Table[g_current.row + i][g_current.col + j] = g_current.array[i][j];
	count = 0;
	// remap Table[][] one line after another from top line
	for (n = 0; n < ROW_MAX; n++)
	{
		sum = 0;
		for (m = 0; m < COL_MAX; m++)
			sum += Table[n][m];
		if (sum == COL_MAX)
		{
			count++;
			// remap above line n of Table[][]
			int l, k;
			for (k = n; k >= 1; k--)
				for (l = 0; l < COL_MAX; l++)
					Table[k][l] = Table[k - 1][l];
			// fill zero at the top line
			for (l = 0; l < COL_MAX; l++)
				Table[k][l] = 0;
			info->timer -= info->decrease--;
		}
	}
	info->final_score += 100 * count; // add to final score
	refresh_g_current_then_check_game_on(info);
}

// switch according to key input using function pointer
void handle_key_press(const char c, t_game_info *info, t_shape temp)
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
        keyFunctions[index](temp, info);
}
