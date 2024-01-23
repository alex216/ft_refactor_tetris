/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_for_shape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaksano <kaksano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:37 by yliu              #+#    #+#             */
/*   Updated: 2024/01/23 14:04:25 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

t_shape	copy_shape(const t_shape shape)
{
	t_shape	new_shape = shape;
	new_shape.array = (char **)calloc(shape.width , sizeof(char *));
	if (!new_shape.array)
		exit(EXIT_FAILURE);

	for (int i = 0; i < shape.width; i++)
	{
		new_shape.array[i] = (char *)malloc(shape.width * sizeof(char));
		if (!new_shape.array[i])
		{
			destruct_shape(new_shape);
			exit(EXIT_FAILURE);
		}
		for (int j = 0; j < shape.width; j++)
			new_shape.array[i][j] = shape.array[i][j];
	}
	return (new_shape);
}

t_shape	create_shape(void)
{
	t_shape new_shape = copy_shape(g_structs_array[rand() % NUMBER_OF_SHAPES]);

	new_shape.col = rand() % (COL - new_shape.width + 1);
	new_shape.row = 0;

	return (new_shape);
}

void	respawn_shape(t_shape *shape)
{
	const t_shape	new_shape = create_shape();

	destruct_shape(*shape);
	*shape = new_shape;

}

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

void	destruct_shape(const t_shape shape)
{
	for (int i = 0; i < shape.width; i++)
		free(shape.array[i]);
	free(shape.array);
}
