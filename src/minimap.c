/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:01:58 by lorey             #+#    #+#             */
/*   Updated: 2025/04/22 05:32:41 by lorey            ###   LAUSANNE.ch       */
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
			my_mlx_pixel_put(&(*img),
				data->player_y * data->mm_ratio + y,
				(data->player_x + x) * data->mm_ratio, GREEN);
	}
}

void	select_tile_and_draw(int x, int y, t_mlx_data *data, t_data *img)
{
	if (data->grid[x][y] == '1')
	{
		data->color = DARK_GRAY;
		draw_square(img, y, x, data);
	}
	else if (data->grid[x][y] == '0')
	{
		data->color = BEIGE;
		draw_square(img, y, x, data);
	}
	else if (data->grid[x][y] == 'D')
	{
		data->color = SADDLE_BROWN;
		draw_square(img, y, x, data);
	}
	else if (data->grid[x][y] == ' ')
	{
		data->color = VIOLET;
		draw_square(img, y, x, data);
	}
}

void	draw_grid(t_data *img, t_mlx_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (data->grid[++y])
	{
		x = -1;
		while (data->grid[y][++x])
		{
			select_tile_and_draw(y, x, data, img);
		}
	}
}
