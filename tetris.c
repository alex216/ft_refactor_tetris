#include "tetris.h"

char			Table[ROW_MAX][COL_MAX] = {0};
struct timeval	before_now, now;
Struct			current;

int	main(void)
{
	int			c;
	Struct		new_shape;
	Struct		temp;
	t_game_info info;
	int			count;

	// initialize
	initiate_game(&info);

	srand(time(0));
	initscr();
	gettimeofday(&before_now, NULL);
	timeout(1);
	new_shape = copy_shape(StructsArray[rand() % 7]);
	new_shape.col = rand() % (COL_MAX - new_shape.width + 1);
	new_shape.row = 0;
	destruct_shape(current);
	current = new_shape;
	if (validate_shape_move(current, &info) == false)
	{
		info.GameOn = false;
	}
	print_screen(&info);
	while (info.GameOn)
	{
		if ((c = getch()) != ERR)
		{
			temp = copy_shape(current);
			switch (c)
			{
			case 's':
				press_s_key(&temp, &info, &new_shape, &count);
				break ;
			case 'd':
				temp.col++;
				if (validate_shape_move(temp, &info))
					current.col++;
				break ;
			case 'a':
				temp.col--;
				if (validate_shape_move(temp, &info))
					current.col--;
				break ;
			case 'w':
				rotate_shape(temp);
				if (validate_shape_move(temp, &info))
					rotate_shape(current);
				break ;
			}
			destruct_shape(temp);
			print_screen(&info);
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate(&info))
		{
			temp = copy_shape(current);
			press_s_key(&temp, &info, &new_shape, &count);
			destruct_shape(temp);
			print_screen(&info);
			gettimeofday(&before_now, NULL);
		}
	}
	destruct_shape(current);
	endwin();
	display_result(&info);
	return (0);
}
