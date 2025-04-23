/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <maambuhl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:14:08 by maambuhl          #+#    #+#             */
/*   Updated: 2025/04/22 15:45:42 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_test(t_mlx_data *data)
{
}

void	check_map_content(t_mlx_data *data)
{
	int		i;
	int		y;
	char	c;
	int		player;

	i = 0;
	player = 0;
	while (data->grid[i])
	{
		y = 0;
		while (data->grid[i][y])
		{
			c = data->grid[i][y];
			if (c != '0' || c != '1' || c != 'N' || c != 'S'
				|| c != 'E' || c != 'W' || c != 'D' || c != ' ')
				err("The map should contain only the following char: 0, 1, N, S, E, W, D, ' '\n", data);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D')
				player++;
			y++;
		}
		i++;
	}
	if (player != 1)
		err("You should provide one player position on the map", data);
}

void	check_map(t_mlx_data *data)
{
	check_map_content(data);
	wall_test(data);
}
