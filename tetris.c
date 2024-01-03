#include "tetris.h"

char			Table[ROW_MAX][COL_MAX] = {0};
struct timeval	before_now, now;
Struct			current;

{
	int i, j;

	{
	}
void	FunctionDS(Struct shape)
{
	int	i;

	for (i = 0; i < shape.width; i++)
	{
		free(shape.array[i]);
	}
	free(shape.array);
}

int	FunctionCP(Struct shape)
{
	char	**array;
	int		i;
	int		j;

	array = shape.array;
	for (i = 0; i < shape.width; i++)
	{
		for (j = 0; j < shape.width; j++)
		{
			if ((shape.col + j < 0 || shape.col + j >= COL_MAX || shape.row + i >= ROW_MAX))
			{
				if (array[i][j])
					return (false);
			}
			else if (Table[shape.row + i][shape.col + j] && array[i][j])
				return (false);
		}
	}
	return (true);
}

void	FunctionRS(Struct shape)
{
	Struct	temp;

	temp = FunctionCS(shape);
	int i, j, k, width;
	width = shape.width;
	for (i = 0; i < width; i++)
	{
		for (j = 0, k = width - 1; j < width; j++, k--)
		{
			shape.array[i][j] = temp.array[k][i];
		}
	}
	FunctionDS(temp);
}

void	print_screen(void)
{
	char	Buffer[ROW_MAX][COL_MAX] = {0};
	int i, j;

	for (i = 0; i < current.width; i++)
	{
		for (j = 0; j < current.width; j++)
		{
			if (current.array[i][j])
				Buffer[current.row + i][current.col + j] = current.array[i][j];
		}
	}
	clear();
	for (i = 0; i < COL_MAX - 9; i++)
		printw(" ");
	printw("42 Tetris\n");
	for (i = 0; i < ROW_MAX; i++)
	{
		for (j = 0; j < COL_MAX; j++)
		{
			printw("%c ", (Table[i][j] + Buffer[i][j]) ? '#' : '.');
		}
		printw("\n");
	}
	printw("\nScore: %d\n", final);
}

int	hasToUpdate(void)
{
	return (((suseconds_t)(now.tv_sec * 1000000 + now.tv_usec)
			- ((suseconds_t)before_now.tv_sec * 1000000
				+ before_now.tv_usec)) > timer);
}

int	main(void)
{
	int		c;
	Struct	new_shape;
	Struct	temp;

	srand(time(0));
	final = 0;
	initscr();
	gettimeofday(&before_now, NULL);
	set_timeout(1);
	new_shape = FunctionCS(StructsArray[rand() % 7]);
	new_shape.col = rand() % (COL_MAX - new_shape.width + 1);
	new_shape.row = 0;
	FunctionDS(current);
	current = new_shape;
	if (!FunctionCP(current))
	{
		GameOn = false;
	}
	print_screen();
	while (GameOn)
	{
		if ((c = getch()) != ERR)
		{
			temp = FunctionCS(current);
			switch (c)
			{
			case 's':
				temp.row++; // move down
				if (FunctionCP(temp))
					current.row++;
				else
				{
					int i, j;
					for (i = 0; i < current.width; i++)
					{
						for (j = 0; j < current.width; j++)
						{
							if (current.array[i][j])
								Table[current.row + i][current.col + j] = current.array[i][j];
						}
					}
					int n, m, sum, count = 0;
					for (n = 0; n < ROW_MAX; n++)
					{
						sum = 0;
						for (m = 0; m < COL_MAX; m++)
						{
							sum += Table[n][m];
						}
						if (sum == COL_MAX)
						{
							count++;
							int l, k;
							for (k = n; k >= 1; k--)
								for (l = 0; l < COL_MAX; l++)
									Table[k][l] = Table[k - 1][l];
							for (l = 0; l < COL_MAX; l++)
								Table[k][l] = 0;
							timer -= decrease--;
						}
					}
					final += 100 * count;
					new_shape = FunctionCS(StructsArray[rand() % 7]);
					new_shape.col = rand() % (COL_MAX - new_shape.width + 1);
					new_shape.row = 0;
					FunctionDS(current);
					current = new_shape;
					if (!FunctionCP(current))
					{
						GameOn = false;
					}
				}
				break ;
			case 'd':
				temp.col++;
				if (FunctionCP(temp))
					current.col++;
				break ;
			case 'a':
				temp.col--;
				if (FunctionCP(temp))
					current.col--;
				break ;
			case 'w':
				FunctionRS(temp);
				if (FunctionCP(temp))
					FunctionRS(current);
				break ;
			}
			FunctionDS(temp);
			print_screen();
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate())
		{
			temp = FunctionCS(current);
			switch ('s')
			{
			case 's':
				temp.row++;
				if (FunctionCP(temp))
					current.row++;
				else
				{
					int i, j;
					for (i = 0; i < current.width; i++)
					{
						for (j = 0; j < current.width; j++)
						{
							if (current.array[i][j])
								Table[current.row + i][current.col + j] = current.array[i][j];
						}
					}
					int n, m, sum, count = 0;
					for (n = 0; n < ROW_MAX; n++)
					{
						sum = 0;
						for (m = 0; m < COL_MAX; m++)
						{
							sum += Table[n][m];
						}
						if (sum == COL_MAX)
						{
							count++;
							int l, k;
							for (k = n; k >= 1; k--)
								for (l = 0; l < COL_MAX; l++)
									Table[k][l] = Table[k - 1][l];
							for (l = 0; l < COL_MAX; l++)
								Table[k][l] = 0;
							timer -= decrease--;
						}
					}
					new_shape = FunctionCS(StructsArray[rand() % 7]);
					new_shape.col = rand() % (COL_MAX - new_shape.width + 1);
					new_shape.row = 0;
					FunctionDS(current);
					current = new_shape;
					if (!FunctionCP(current))
					{
						GameOn = false;
					}
				}
				break ;
			case 'd':
				temp.col++;
				if (FunctionCP(temp))
					current.col++;
				break ;
			case 'a':
				temp.col--;
				if (FunctionCP(temp))
					current.col--;
				break ;
			case 'w':
				FunctionRS(temp);
				if (FunctionCP(temp))
					FunctionRS(current);
				break ;
			}
			FunctionDS(temp);
			print_screen();
			gettimeofday(&before_now, NULL);
		}
	}
	FunctionDS(current);
	endwin();
	int i, j;
	for (i = 0; i < ROW_MAX; i++)
	{
		for (j = 0; j < COL_MAX; j++)
		{
			printf("%c ", Table[i][j] ? '#' : '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", final);
	return (0);
}
