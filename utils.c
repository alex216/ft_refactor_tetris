#include "tetris.h"

void	refresh_g_current_then_game_on(t_game_info *info, t_shape *new_shape);

// create new shape and check if game over
void	refresh_g_current_then_game_on(t_game_info *info, t_shape *new_shape)
{
	*new_shape = create_shape();
	destruct_shape(g_current);
	g_current = *new_shape;
	if (check_shape(g_current, info) == false)
		info->GameOn = false;
}
