#include "../inc/tetris.h"

static void	_move_right(t_shape temp, t_game_info *info);
static void _move_left(t_shape temp, t_game_info *info);
static void _move_rotate(t_shape temp, t_game_info *info);
static void _compound_func(t_game_info *info);
void 		control_key_press(const char c, t_game_info *info, t_shape temp);

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
static void _move_rotate(t_shape temp, t_game_info *info)
{
    rotate_shape(temp);
    if (check_shape(temp, info))
        rotate_shape(g_current);
}

// switch according to key input using function pointer
void control_key_press(const char c, t_game_info *info, t_shape temp)
{
	int	index = -1;
	const switch_keypress_behaviour keyFunctions[] = {
		move_down,
		_move_right,
		_move_left,
		_move_rotate
	};

    switch (c) {
        case 's': index = 0; break;
        case 'd': index = 1; break;
        case 'a': index = 2; break;
        case 'w': index = 3; break;
		default : break;
    }
    if (index != -1)
        keyFunctions[index](temp, info);
}
