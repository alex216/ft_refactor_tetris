#include "tetris.h"

// global definitions
char			Table[ROW_MAX][COL_MAX] = {0};
struct timeval	before_now, now;
t_shape			g_current;
const t_shape	g_StructsArray[NUMBER_OF_TOTAL_SHAPES] = {
	{(char *[]){(char[]){0, 1, 1},
				(char[]){1, 1, 0},
				(char[]){0, 0, 0}}, 3
	},
	{(char *[]){(char[]){1, 1, 0},
				(char[]){0, 1, 1},
				(char[]){0, 0, 0}}, 3
	},
	{(char *[]){(char[]){0, 1, 0},
				(char[]){1, 1, 1},
				(char[]){0, 0, 0}}, 3
	},
	{(char *[]){(char[]){0, 0, 1},
				(char[]){1, 1, 1},
				(char[]){0, 0, 0}}, 3
	},
	{(char *[]){(char[]){1, 0, 0},
				(char[]){1, 1, 1},
				(char[]){0, 0, 0}}, 3
	},
	{(char *[]){(char[]){1, 1},
				(char[]){1, 1}}, 2
	},
	{(char *[]){(char[]){0, 0, 0, 0},
				(char[]){1, 1, 1, 1},
				(char[]){0, 0, 0, 0},
				(char[]){0, 0, 0, 0}}, 4
	}
};

// copy_shape, handle_key_input, free shape, then print
static void _manage_a_frame(char c, t_game_info *info, t_shape *new_shape, int *count)
{
	t_shape temp;

	temp = copy_shape(g_current);
	handle_key_press(c, info, new_shape, count, &temp);
	destruct_shape(temp);
	print_screen(info);
}

int	main(void)
{
	t_game_info info;
	t_shape		new_shape;
	int			c;
	int			count;

	// initialize
	initiate_game(&info);
	srand(time(0));
	initscr();
	gettimeofday(&before_now, NULL);
	timeout(1);

	// create first shape
	refresh_g_current_then_game_on(&info, &new_shape);

	print_screen(&info);
	while (info.GameOn)
	{
		if ((c = getch()) != ERR)
		{
			_manage_a_frame(c, &info, &new_shape, &count);
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate(&info))
		{
			_manage_a_frame('s', &info, &new_shape, &count);
			gettimeofday(&before_now, NULL);
		}
	}
	destruct_shape(g_current);
	endwin();
	display_result(&info);
	return (0);
}
