/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:44:15 by lorey             #+#    #+#             */
/*   Updated: 2025/04/06 21:04:01 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

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
	data->angle_bkp = data->angle;
}

void	set_next_pos(int next_x, int next_y, t_mlx_data *data)
{
	if (data->grid[next_x / TILE_SIZE][next_y / TILE_SIZE] != '1')
	{
		data->player_x = next_x;
		data->player_y = next_y;
	}
}

int	handle_key(int keysym, t_mlx_data *data)
{
	int	next_x;
	int	next_y;

	change_angle(keysym, data);
	if (keysym == XK_w)
	{
		next_x = MV_SPD * cos(data->angle_bkp) + data->player_x;
		next_y = MV_SPD * sin(data->angle_bkp) + data->player_y;
		set_next_pos(next_x, next_y, data);
	}
	else if (keysym == XK_s)
	{
		next_x = data->player_x - MV_SPD * cos(data->angle_bkp);
		next_y = data->player_y - MV_SPD * sin(data->angle_bkp);
		set_next_pos(next_x, next_y, data);
	}
	else if (keysym == XK_d)
	{
		next_x = data->player_x - MV_SPD * sin(data->angle_bkp);
		next_y = data->player_y + MV_SPD * cos(data->angle_bkp);
		set_next_pos(next_x, next_y, data);
	}
	else if (keysym == XK_a)
	{
		next_x = data->player_x + MV_SPD * sin(data->angle_bkp);
		next_y = data->player_y - MV_SPD * cos(data->angle_bkp);
		set_next_pos(next_x, next_y, data);
	}
	return (0);
}

void	draw_rays(t_mlx_data *data)
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
	t_data	*minimap_img;
	t_data	*img_3d;

	minimap_img = data->img_ptr;
	img_3d = data->raycast;
	draw_minimap_background(minimap_img);
	draw_grid(minimap_img, data);
	draw_player(minimap_img, data);
	draw_3d_top(img_3d);
	draw_3d_bottom(img_3d);
	draw_rays(data);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_3d->img, 500, 0);
	mlx_put_image_to_window(
		data->mlx_ptr, data->win_ptr, minimap_img->img, 0, 0);
	return (0);
}
