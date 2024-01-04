#include "tetris.h"

void	refresh_g_current_then_check_game_on(t_game_info *info);

// create new shape and check if game over
void	refresh_g_current_then_check_game_on(t_game_info *info)
{
	// refresh g current
	const t_shape	new_shape = create_shape();
	destruct_shape(g_current);
	g_current = new_shape;

	// check whether game may continue
	if (check_shape(g_current, info) == false)
		info->GameOn = false;
}
