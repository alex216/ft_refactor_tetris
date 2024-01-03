#include "tetris.h"

int		check_shape(Struct shape, t_game_info *info);
Struct	copy_shape(Struct shape);
void	rotate_shape(Struct shape);
void	destruct_shape(Struct shape);

/**
 * @brief   Checks if placing the given shape at its current position is valid.
 *
 * This function verifies whether placing the provided shape at its current
 * position on the game table is a valid move. It checks for collisions with
 * the boundaries of the game table and other occupied cells.
 *
 * @param   shape   The input shape to be checked.
 * @return  Returns true if placing the shape is valid, and false otherwise.
 */
int	check_shape(Struct shape, t_game_info *info)
{
	char	**array;
	int		i;
	int		j;

	array = shape.array;
	for (i = 0; i < shape.width; i++)
		for (j = 0; j < shape.width; j++)
			if (IS_CELL_OCCUPIED && (IS_OUTSIDE_BOUNDS || IS_TABLE_OCCUPIED))
				return (false);
	return (true);
}

/**
 * @brief   Creates a copy of the given shape.
 *
 * This function takes a Struct representing a shape and creates a new copy
 * of it. The original shape remains unchanged, and the copied shape is
 * returned.
 *
 * @param   shape   The input shape to be copied.
 * @return  A new shape that is a copy of the input shape.
 */
Struct	copy_shape(Struct shape)
{
	Struct	new_shape;
	int i, j;

	new_shape = shape;
	new_shape.array = (char **)malloc(new_shape.width * sizeof(char *));
	for (i = 0; i < new_shape.width; i++)
	{
		new_shape.array[i] = (char *)malloc(new_shape.width * sizeof(char));
		for (j = 0; j < new_shape.width; j++)
			new_shape.array[i][j] = shape.array[i][j];
	}
	return (new_shape);
}

/**
 * @brief   Rotates the given shape 90 degrees clockwise.
 *
 * This function takes a Struct representing a shape and rotates it 90 degrees
 * clockwise. The original shape remains unchanged, and the rotated shape is
 * returned.
 *
 * @param   shape   The input shape to be rotated.
 */
void	rotate_shape(Struct shape)
{
	Struct	temp;
	int y, rx, x, ry;

	temp = copy_shape(shape);
	for (y = 0; y < shape.width; y++)
	{
		for (x = 0; x < shape.width; x++)
		{
			if (ROTATE_CLOCKWISE == true)
			{
				ry = y;
				rx = (shape.width - 1) - x;
			}
			else
			{
				ry = (shape.width - 1) - y;
				rx = x;
			}
			shape.array[ry][rx] = temp.array[x][y];
		}
	}
	destruct_shape(temp);
}

/**
 * @brief Free struct shape.
 *
 * @param	shapt	The input shape to be freed.
 */
void	destruct_shape(Struct shape)
{
	int	i;

	for (i = 0; i < shape.width; i++)
		free(shape.array[i]);
	free(shape.array);
}
