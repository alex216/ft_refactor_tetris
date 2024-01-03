#include "tetris.h"

// TODO: rotate q and e key

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

int	main(void)
{
	int			c;
	t_shape		new_shape;
	t_shape		temp;
	t_game_info info;
	int			count;

	// initialize
	initiate_game(&info);

	srand(time(0));
	initscr();
	gettimeofday(&before_now, NULL);
	timeout(1);
	new_shape = copy_shape(g_StructsArray[rand() % NUMBER_OF_TOTAL_SHAPES]);
	new_shape.col = rand() % (COL_MAX - new_shape.width + 1);
	new_shape.row = 0;
	destruct_shape(g_current);
	g_current = new_shape;
	if (check_shape(g_current, &info) == false)
	{
		info.GameOn = false;
	}
	print_screen(&info);
	while (info.GameOn)
	{
		if ((c = getch()) != ERR)
		{
			temp = copy_shape(g_current);
			handle_key_press(c, &info, &new_shape, &count, &temp);
			// switch (c)
			// {
			// case 's':
			// 	press_s_key(&temp, &info, &new_shape, &count);
			// 	break ;
			// case 'd':
			// 	temp.col++;
			// 	if (check_shape(temp, &info))
			// 		g_current.col++;
			// 	break ;
			// case 'a':
			// 	temp.col--;
			// 	if (check_shape(temp, &info))
			// 		g_current.col--;
			// 	break ;
			// case 'w':
			// 	rotate_shape(temp);
			// 	if (check_shape(temp, &info))
			// 		rotate_shape(g_current);
			// 	break ;
			// }
			destruct_shape(temp);
			print_screen(&info);
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate(&info))
		{
			temp = copy_shape(g_current);
			press_s_key(&temp, &info, &new_shape, &count);
			destruct_shape(temp);
			print_screen(&info);
			gettimeofday(&before_now, NULL);
		}
	}
	destruct_shape(g_current);
	endwin();
	display_result(&info);
	return (0);
}
