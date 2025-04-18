/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:01:58 by lorey             #+#    #+#             */
/*   Updated: 2025/04/18 02:51:18 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_background(t_data *img)
{
	int	x;
	int	y;

	x = -1;
	while (++x < SIZE_MAP_X)
	{
		y = -1;
		while (++y < SIZE_MAP_Y)
			my_mlx_pixel_put(&(*img), x, y, BLACK);
	}
}

void	draw_player(t_data *img, t_mlx_data *data)
{
	int	x;
	int	y;

	x = -6;
	while (++x < 5)
	{
		y = -6;
		while (++y < 5)
			my_mlx_pixel_put(&(*img), (data->player_x + x) * data->mm_ratio,
				data->player_y * data->mm_ratio + y, GREEN);
	}
}

void	draw_grid(t_data *img, t_mlx_data *data)
{
	int	x;
	int	y;

	x = -1;
	while (data->grid[++x])
	{
		y = -1;
		while (data->grid[x][++y])
		{
			if (data->grid[x][y] == '1')
				draw_square(img, x, y, DARK_GRAY, data);
			else if (data->grid[x][y] == '0')
				draw_square(img, x, y, BEIGE, data);
			else if (data->grid[x][y] == 'D')
				draw_square(img, x, y, SADDLE_BROWN, data);
		}
	}
}

void	size_array(t_mlx_data *data)
{
	int	i;
	int	j;
	int	tmp;

	i = -1;
	j = 0;
	tmp = 0;
	while (data->grid[++i])
	{
		tmp = ft_strlen(data->grid[i]);
		if (tmp > j)
			j = tmp;
	}
	data->tile_x_nbr = i;
	data->tile_y_nbr = j;
	if (i > j)
		data->tile_max_nbr = i;
	else
		data->tile_max_nbr = j;
	if (i >= 10 || j >= 10)
		data->mm_ratio = 500 / (data->tile_max_nbr * TILE_SIZE);
	else
		data->mm_ratio = 1;
}
