/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:43:38 by lorey             #+#    #+#             */
/*   Updated: 2025/04/06 20:53:27 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_data *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (++i < TILE_SIZE - 1)
	{
		j = 1;
		while (++j < TILE_SIZE - 1)
			my_mlx_pixel_put(
				&(*img), x * TILE_SIZE + i, y * TILE_SIZE + j, color);
	}
}

void	draw_line(t_mlx_data *data, int x1, int y1, int x2, int y2, int color)
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	sx = (x1 < x2) ? 1 : -1;
	sy = (y1 < y2) ? 1 : -1;
	err = dx - dy;

	while (1)
	{
		if (x1 >= 0 && x1 < data->size_x_window && y1 >= 0 && y1 < data->size_y_window)
			my_mlx_pixel_put(&(*data->img_ptr), x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err = err - dy;
			x1 = x1 + sx;
		}
		if (e2 < dx)
		{
			err = err + dx;
			y1 = y1 + sy;
		}
	}
}
