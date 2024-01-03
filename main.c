#include "tetris.h"

void		_initiate_game(t_game_info *info);
int			_check_autoupdate(t_game_info *info);
void		_print_screen(t_game_info *info);
static void _manage_a_frame(char c, t_game_info *info, t_shape *new_shape, int *count);
static void	_process_tetris(char c, t_game_info *info, t_shape *new_shape, int *count);
static void	_display_result(t_game_info *info);
int			main(void);

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

// initialize t_game_info struct variable
void	_initiate_game(t_game_info *info)
{
	info->final_score = 0;
	info->timer = STARTING_TIME;
	info->GameOn = true;
	info->decrease = DEFAULT_DECREASE_SPEED;
}

// checks if it is time to update the game state based on a timer
int	_check_autoupdate(t_game_info *info)
{
	suseconds_t current_time;
	suseconds_t previous_time;

	current_time = now.tv_sec * INTERVAL_MICROSECONDS + now.tv_usec;
	previous_time = before_now.tv_sec * INTERVAL_MICROSECONDS + before_now.tv_usec;
	if (current_time - previous_time > info->timer)
		return (true);
	else
		return (false);
}

// copy shape to Buffer, then print both Table and Buffer
void	_print_screen(t_game_info *info)
{
	char	Buffer[ROW_MAX][COL_MAX] = {0};
	int i, j;

	// copy g_current to Buffer
	for (i = 0; i < g_current.width; i++)
		for (j = 0; j < g_current.width; j++)
			if (g_current.array[i][j])
				Buffer[g_current.row + i][g_current.col + j] = g_current.array[i][j];
	clear();
	for (i = 0; i < COL_MAX - 9; i++)
		printw(" ");
	printw("42 Tetris\n");
	for (i = 0; i < ROW_MAX; i++)
	{
		for (j = 0; j < COL_MAX; j++)
			// calculate Table and Buffer
			printw("%c ", (Table[i][j] + Buffer[i][j]) ? BLOCK_CHAR : BLANK_CHAR);
		printw("\n");
	}
	printw("\nScore: %d\n", info->final_score);
}

// copy_shape, handle_key_input, free shape, then print
static void _manage_a_frame(char c, t_game_info *info, t_shape *new_shape, int *count)
{
	t_shape temp;

	temp = copy_shape(g_current);
	handle_key_press(c, info, new_shape, count, &temp);
	destruct_shape(temp);
	_print_screen(info);
}

// process main tetris program
static void	_process_tetris(char c, t_game_info *info, t_shape *new_shape, int *count)
{
	// set the length of time getch() waits for input
	timeout(1);
	while (info->GameOn)
	{
		if ((c = getch()) != ERR)
		{
			_manage_a_frame(c, info, new_shape, count);
		}
		gettimeofday(&now, NULL);
		if (_check_autoupdate(info))
		{
			_manage_a_frame('s', info, new_shape, count);
			gettimeofday(&before_now, NULL);
		}
	}
}

// display result
static void	_display_result(t_game_info *info)
{
	int x, y;
	for (x = 0; x < ROW_MAX; x++)
	{
		for (y = 0; y < COL_MAX; y++)
			printf("%c ", Table[x][y] ? BLOCK_CHAR : BLANK_CHAR);
		printf("\n");
	}
	printf("\nGame over!\n\nScore: %d\n", info->final_score);
}

int	main(void)
{
	t_game_info info;
	t_shape		new_shape;
	int			c;
	int			count;

	// initialize
	_initiate_game(&info);
	srand(time(0));
	initscr();
	gettimeofday(&before_now, NULL);

	// create first shape then print
	refresh_g_current_then_game_on(&info, &new_shape);
	_print_screen(&info);

	// exec game unless GameOn is false during executing _manage_a_frame
	_process_tetris(c, &info, &new_shape, &count);

	// finish program
	destruct_shape(g_current);
	endwin();
	_display_result(&info);
	return (0);
}
