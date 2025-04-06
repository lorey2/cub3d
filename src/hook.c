/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:44:15 by lorey             #+#    #+#             */
/*   Updated: 2025/04/06 11:34:26 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int	close_cross(t_mlx_data *data)
{
	data->player_x = 0;
	exit (0);
	return (0);
}

void	change_angle(int keysym, t_mlx_data *data)
{
	if (keysym == XK_q)
	{
		data->angle -= (M_PI / 180);
		if (data->angle < -2 * M_PI)
			data->angle = 0;
	}
	if (keysym == XK_e)
	{
		data->angle += (M_PI / 180);
		if (data->angle > 2 * M_PI)
			data->angle = 0;
	}
}

int	handle_key(int keysym, t_mlx_data *data)
{
	change_angle(keysym, data);
	if (keysym == XK_w
		&& data->grid[data->player_x / TILE_SIZE]
		[(data->player_y - MV_SPD) / TILE_SIZE] != '1')
		data->player_y -= MV_SPD;
	if (keysym == XK_s
		&& data->grid[data->player_x / TILE_SIZE]
		[(data->player_y + MV_SPD) / TILE_SIZE] != '1')
		data->player_y += MV_SPD;
	if (keysym == XK_d
		&& data->grid[(data->player_x + MV_SPD) / TILE_SIZE]
		[data->player_y / TILE_SIZE] != '1')
		data->player_x += MV_SPD;
	if (keysym == XK_a
		&& data->grid[(data->player_x - MV_SPD) / TILE_SIZE]
		[data->player_y / TILE_SIZE] != '1')
		data->player_x -= MV_SPD;
	return (0);
}

void	draw_3d(t_mlx_data *data, int ray)
{
	int	square_size;
	int	i;
	int	j;

	j = -1;
	square_size = S_RAY_X / RAY_NUMBER;
	while (++j < square_size)
	{
		i = -1;
//		data->best *= cos(data->best - data->angle_bkp);
		while (++i < 10000 / data->best)
		{
			if (10000 / data->best < 500)
			{

				my_mlx_pixel_put(&(*data->raycast), j + ray * square_size, i + 500, data->color);
				my_mlx_pixel_put(&(*data->raycast), j + ray * square_size, 500 - i, data->color);
			}
		}
	}
}

void	draw_lines(t_mlx_data *data)
{
	double	angle_bkp;
	double	angle_delta;
	double	left_most_ray_angle;
	int		i;
	double	fov;
	double	ray_number;

	fov = FOV;
	ray_number = RAY_NUMBER;
	angle_bkp = data->angle;
	angle_delta = (fov / ray_number) * 2 * M_PI / 360;
	left_most_ray_angle = data->angle - ((fov / 2) * ((2 * M_PI) / 360));
	i = 0;
	data->angle = left_most_ray_angle;
	while (++i < RAY_NUMBER)
	{
		draw_best_line(data);
		draw_3d(data, i);
		data->angle += angle_delta;
	}
	data->angle = angle_bkp;
}

int	display(t_mlx_data *data)
{
	int		x;
	int		y;
	t_data	*img;
	t_data	*img_2;

	img = data->img_ptr;
	img_2 = data->raycast;
	x = -1;
	y = -1;
	while (++x < 500)
	{
		y = -1;
		while (++y < 500)
			my_mlx_pixel_put(&(*img), x, y, RED);
	}
	x = -1;
	while (++x < 1000)
	{
		y = -1;
		while (++y < 500)
			my_mlx_pixel_put(&(*data->raycast), x, y, RED);
	}
	x = -1;
	while (++x < 1000)
	{
		y = 499;
		while (++y < 1000)
			my_mlx_pixel_put(&(*data->raycast), x, y, CYAN);
	}
	draw_grid(img, data);
	draw_player(img, data);
	draw_lines(data);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_2->img, 500, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img->img, 0, 0);
	return (0);
}

int	close_esc(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
	{
		data->player_x = 0;
		exit (0);
		return (0);
	}
	return (0);
}
