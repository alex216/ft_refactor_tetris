#include "tetris.h"

void		_initialize_game(t_game_info *info);
t_bool		_check_if_has_to_update(t_game_info *info);
void		_print_screen(t_game_info *info);
static void _manage_frame(const char c, t_game_info *info);
static void	_process_tetris(t_game_info *info);
static void	_display_result(t_game_info *info);
int			main(void);


// initialize t_game_info struct variable
void	_initialize_game(t_game_info *info)
{
	// set score to zero
	info->final_score = 0;

	// set starting interval of game speed 
	info->timer = STARTING_TIME;

	// set variable to control game to continue
	info->GameOn = true;

	// set speed of decreasing regarding interval
	info->decrease = DEFAULT_DECREASE_SPEED;

	// set current time
	gettimeofday(&(info->before_now), NULL);
}

// checks if it is time to update the game state based on a timer
t_bool	_check_if_has_to_update(t_game_info *info)
{
	suseconds_t current_time = info->now.tv_sec * INTERVAL_MICROSECONDS + info->now.tv_usec;
	suseconds_t previous_time = info->before_now.tv_sec * INTERVAL_MICROSECONDS + info->before_now.tv_usec;

	return (current_time - previous_time > info->timer);
}

// copy shape to Buffer, then print both Table and Buffer
void	_print_screen(t_game_info *info)
{
	char	Buffer[ROW_MAX][COL_MAX] = {0};

	// copy g_current to Buffer
	copy_g_current_shape_to_map(&Buffer);

	// clear screen, print game title
	clear();
	for (int i = 0; i < COL_MAX - 9; i++)
		printw(" ");
	printw("42 Tetris\n");

	// display block and blank by adding Table and Buffer
	for (int i = 0; i < ROW_MAX; i++)
	{
		for (int j = 0; j < COL_MAX; j++)
			printw("%c ", (Table[i][j] + Buffer[i][j]) ? BLOCK_CHAR : BLANK_CHAR);
		printw("\n");
	}

	// display current score
	printw("\nScore: %d\n", info->final_score);
}

// copy_shape, handle_key_input, free shape, then print
static void _manage_frame(const char c, t_game_info *info)
{
	t_shape temp = copy_shape(g_current);

	control_key_press(c, info, temp);
	destruct_shape(temp);
	_print_screen(info);
}

// process main tetris program
static void	_process_tetris(t_game_info *info)
{
	char c;

	// set the length of time getch() waits for input
	timeout(1);
	while (info->GameOn)
	{
		// check key input is valid
		if ((c = getch()) != ERR)
			_manage_frame(c, info);
		// check time to update no matter key input
		gettimeofday(&(info->now), NULL);
		if (_check_if_has_to_update(info))
		{
			info->is_s_key_fall = false;
			_manage_frame('s', info);
			gettimeofday(&(info->before_now), NULL);
			info->is_s_key_fall = true;
		}
	}
}

// display result
static void	_display_result(t_game_info *info)
{
	for (int x = 0; x < ROW_MAX; x++)
	{
		for (int y = 0; y < COL_MAX; y++)
			printf("%c ", Table[x][y] ? BLOCK_CHAR : BLANK_CHAR);
		printf("\n");
	}
	printf("\nGame over!\n\nScore: %d\n", info->final_score);
}

int	main(void)
{
	t_game_info info;

	// initialize
	_initialize_game(&info);
	srand(time(0));
	initscr();

	// exec game unless GameOn is false during executing _manage_a_frame
	refresh_g_current_then_check_game_on(&info);
	_print_screen(&info);
	_process_tetris(&info);

	// finish program
	destruct_shape(g_current);
	endwin();
	_display_result(&info);

	return (0);
}
