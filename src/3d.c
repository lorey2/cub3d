/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:37:32 by lorey             #+#    #+#             */
/*   Updated: 2025/04/06 21:02:54 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_3d_top(t_data *img_3d)
{
	int	x;
	int	y;

	x = -1;
	while (++x < 1000)
	{
		y = 499;
		while (++y < 1000)
			my_mlx_pixel_put(&(*img_3d), x, y, CYAN);
	}
}

void	draw_3d_bottom(t_data *img_3d)
{
	int	x;
	int	y;

	x = -1;
	while (++x < 1000)
	{
		y = -1;
		while (++y < 500)
			my_mlx_pixel_put(&(*img_3d), x, y, RED);
	}
}

void	draw_3d(t_mlx_data *data, int ray)
{
	int	square_size;
	int	i;
	int	j;

	j = -1;
	data->best *= cos(data->angle - data->angle_bkp);
	data->best /= 2;
	square_size = S_RAY_X / RAY_NUMBER;
	while (++j < square_size)
	{
		i = -1;
		while (++i < 10000 / data->best && i + 500 < 1000 && 500 - i > 0)
		{
			my_mlx_pixel_put(&(*data->raycast),
				j + ray * square_size, i + 500, data->color);
			my_mlx_pixel_put(&(*data->raycast),
				j + ray * square_size, 500 - i, data->color);
		}
	}
}
