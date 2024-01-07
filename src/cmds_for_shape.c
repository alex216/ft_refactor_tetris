/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_for_shape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:37 by yliu              #+#    #+#             */
/*   Updated: 2024/01/07 14:22:22 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/tetris.h"

// create new shape
t_shape	create_shape(void)
{
	t_shape new_shape = copy_shape(g_StructsArray[rand() % NUMBER_OF_TOTAL_SHAPES]);

	new_shape.col = rand() % (COL_MAX - new_shape.width + 1);
	new_shape.row = 0;

	return (new_shape);
}

// checks if placing the given shape at its current position is valid
int	check_shape_with_map(const t_shape shape)
{
	const char	**array = (const char **)shape.array;

	for (int i = 0; i < shape.width; i++)
		for (int j = 0; j < shape.width; j++)
			if (IS_CELL_OCCUPIED && (IS_OUTSIDE_BOUNDS || IS_TABLE_OCCUPIED))
				return (false);
	return (true);
}

// creates a copy of the given shape
t_shape	copy_shape(const t_shape shape)
{
	t_shape	new_shape = shape;
	new_shape.array = (char **)malloc(shape.width * sizeof(char *));

	for (int i = 0; i < shape.width; i++)
	{
		new_shape.array[i] = (char *)malloc(shape.width * sizeof(char));
		for (int j = 0; j < shape.width; j++)
			new_shape.array[i][j] = shape.array[i][j];
	}
	return (new_shape);
}

// rotates the given shape 90 degrees clockwise
void	rotate_shape(const t_shape shape)
{
	int rx, ry;
	const t_shape	temp = copy_shape(shape);

	for (int y = 0; y < shape.width; y++)
	{
		for (int x = 0; x < shape.width; x++)
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

// free struct shape
void	destruct_shape(const t_shape shape)
{
	for (int i = 0; i < shape.width; i++)
		free(shape.array[i]);
	free(shape.array);
}
