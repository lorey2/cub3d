/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:01:58 by lorey             #+#    #+#             */
/*   Updated: 2025/04/06 20:03:56 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_background(t_data *img)
{
	int	x;
	int	y;

	x = -1;
	while (++x < 500)
	{
		y = -1;
		while (++y < 500)
			my_mlx_pixel_put(&(*img), x, y, RED);
	}
}

void	draw_player(t_data *img, t_mlx_data *data)
{
	int	x;
	int	y;

	x = -1;
	while (++x < 10)
	{
		y = -1;
		while (++y < 10)
			my_mlx_pixel_put(&(*img), data->player_x + x,
				data->player_y + y, GREEN);
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
				draw_square(img, x, y, BLUE);
			else if (data->grid[x][y] == '0')
				draw_square(img, x, y, BLACK);
		}
	}
}
