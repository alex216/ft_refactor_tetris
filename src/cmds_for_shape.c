/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_for_shape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:37:37 by yliu              #+#    #+#             */
/*   Updated: 2024/01/23 15:01:49 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

t_block	copy_block(const t_block block)
{
	t_block	new_block = block;
	new_block.array = (char **)calloc(block.width , sizeof(char *));
	if (!new_block.array)
		exit(EXIT_FAILURE);

	for (int i = 0; i < block.width; i++)
	{
		new_block.array[i] = (char *)malloc(block.width * sizeof(char));
		if (!new_block.array[i])
		{
			destruct_block(new_block);
			exit(EXIT_FAILURE);
		}
		for (int j = 0; j < block.width; j++)
			new_block.array[i][j] = block.array[i][j];
	}
	return (new_block);
}

t_block	create_block(void)
{
	t_block new_block = copy_block(g_structs_array[rand() % NUMBER_OF_blockS]);

	new_block.col = rand() % (COL - new_block.width + 1);
	new_block.row = 0;

	return (new_block);
}

void	respawn_block(t_block *block)
{
	const t_block	new_block = create_block();

	destruct_block(*block);
	*block = new_block;

}

void	rotate_block(const t_block block)
{
	int rx, ry;
	const t_block	temp = copy_block(block);

	for (int y = 0; y < block.width; y++)
	{
		for (int x = 0; x < block.width; x++)
		{
			if (ROTATE_CLOCKWISE == true)
			{
				ry = y;
				rx = (block.width - 1) - x;
			}
			else
			{
				ry = (block.width - 1) - y;
				rx = x;
			}
			block.array[ry][rx] = temp.array[x][y];
		}
	}
	destruct_block(temp);
}

void	destruct_block(const t_block block)
{
	for (int i = 0; i < block.width; i++)
		free(block.array[i]);
	free(block.array);
}
