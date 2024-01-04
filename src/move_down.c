#include "../inc/tetris.h"

static void _remap_table(const int max_row);
static void _count_vanish_line_then_add_score(t_game_info *info);
void		move_down(t_shape temp, t_game_info *info);

// remap from above
void	_remap_table(const int max_row)
{
	// remap above line n of Table[][]
	for (int i = max_row; i >= 1; i--)
		for (int j = 0; j < COL_MAX; j++)
			Table[i][j] = Table[i - 1][j];
	// fill zero at the top line
	for (int j = 0; j < COL_MAX; j++)
		Table[0][j] = 0;
}

// count tetris vanish line
static void _count_vanish_line_then_add_score(t_game_info *info)
{
	int sum, count;

	count = 0;
	// remap Table[][] one line after another from top line
	for (int n = 0; n < ROW_MAX; n++)
	{
		sum = 0;
		for (int m = 0; m < COL_MAX; m++)
			sum += Table[n][m];
		if (sum == COL_MAX)
		{
			count++;
			_remap_table(n);
			info->timer -= info->decrease--;
		}
	}
	// choose to obay original code or pdf
	#ifdef OBAY_ORIGINAL_CODE
	if (info->is_s_key_fall == true)
		info->final_score += 100 * count * COL_MAX;
	#else
	info->final_score += 100 * count * COL_MAX;
	#endif
}

// move down
void	move_down(t_shape temp, t_game_info *info)
{
	temp.row++;
	if (check_shape(temp, info) == true)
		g_current.row++;
	else
	{
		// copy global shape to global Table
		copy_g_current_shape_to_map(&Table);

		// refresh score
		_count_vanish_line_then_add_score(info);

		// refresh global shape
		refresh_g_current_then_check_game_on(info);
	}
}
