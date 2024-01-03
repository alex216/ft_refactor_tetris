#include "tetris.h"

void move_right(t_shape *temp, t_game_info *info, t_shape *new_shape, int *count){
    temp->col++;
    if (check_shape(*temp, info)) {
        g_current.col++;
    }
}

void move_left(t_shape *temp, t_game_info *info, t_shape *new_shape, int *count){
    temp->col--;
    if (check_shape(*temp, info)) {
        g_current.col--;
    }
}

void rotate(t_shape *temp, t_game_info *info, t_shape *new_shape, int *count){
    rotate_shape(*temp);
    if (check_shape(*temp, info)) {
        rotate_shape(g_current);
    }
}

// Function prototypes
typedef void (*switch_keypress_behaviour)(t_shape *, t_game_info *, t_shape *, int *);

void handle_key_press(char c, t_game_info *info, t_shape *new_shape, int *count, t_shape *temp)
{
	int	index;

    switch_keypress_behaviour keyFunctions[] = {
		press_s_key,
		move_right,
		move_left,
		rotate
	};
    index = -1;
    switch (c) {
        case 's': index = 0; break;
        case 'd': index = 1; break;
        case 'a': index = 2; break;
        case 'w': index = 3; break;
		default : break;
    }
    if (index != -1)
        keyFunctions[index](temp, info, new_shape, count);
}

