#include "tetris.h"

int		check_shape(t_shape shape, t_game_info *info);
t_shape	copy_shape(t_shape shape);
void	rotate_shape(t_shape shape);
void	destruct_shape(t_shape shape);

/**
 * @brief   Checks if placing the given shape at its current position is valid.
 *
 * @param   shape	The input shape to be checked.
 * 			info
 * @return  int		True if placing the shape is valid, and false otherwise.
 */
int	check_shape(t_shape shape, t_game_info *info)
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
 * @brief	Creates a copy of the given shape.
 *
 * @param	t_shape	The input shape to be copied.
 * @return	t_shape	A new shape that is a copy of the input shape.
 */
t_shape	copy_shape(t_shape shape)
{
	t_shape	new_shape;
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
 * @param   shape   The input shape to be rotated.
 */
void	rotate_shape(t_shape shape)
{
	t_shape	temp;
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
 * @brief	Free struct shape.
 *
 * @param	shapt	The input shape to be freed.
 */
void	destruct_shape(t_shape shape)
{
	int	i;

	for (i = 0; i < shape.width; i++)
		free(shape.array[i]);
	free(shape.array);
}
