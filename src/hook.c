/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:44:10 by lorey             #+#    #+#             */
/*   Updated: 2025/04/11 05:28:27 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	draw_rays(t_mlx_data *data)
{
	double	angle_bkp;
	double	angle_delta;
	double	left_most_ray_angle;
	int		i;

	angle_bkp = data->angle;
	angle_delta = (FOV / RAY_NUMBER) * 2 * M_PI / 360;
	left_most_ray_angle = data->angle - ((FOV / 2) * ((2 * M_PI) / 360));
	i = -1;
	data->angle = left_most_ray_angle;
	while (++i < RAY_NUMBER)
	{
		if (data->angle > 2 * M_PI)
			data->angle -= 2 * M_PI;
		if (data->angle < -2 * M_PI)
			data->angle += 2 * M_PI;
		draw_best_line(data);
		draw_3d(data, i);
		data->angle += angle_delta;
	}
	data->angle = angle_bkp;
}

void	wait_for_next_frame(void)
{
	struct timeval			current_time;
	static struct timeval	last_frame_time;
	double					elapsed_time;
	double					target_frame_time;

	target_frame_time = 1.0 / FPS;
	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec - last_frame_time.tv_sec)
		+ (current_time.tv_usec - last_frame_time.tv_usec) / 1000000.0;
	if (elapsed_time < target_frame_time)
	{
		usleep((target_frame_time - elapsed_time) * 1000000);
		gettimeofday(&current_time, NULL);
	}
	last_frame_time = current_time;
}

int	display(t_mlx_data *data)
{
	t_data					*minimap_img;
	t_data					*img_3d;

	wait_for_next_frame();
	minimap_img = data->img_ptr;
	img_3d = data->raycast;
	handle_key(data);
	change_angle(data);
	draw_minimap_background(minimap_img);
	draw_grid(minimap_img, data);
	draw_player(minimap_img, data);
	draw_3d_top(img_3d);
	draw_3d_bottom(img_3d);
	draw_rays(data);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_3d->img,
		POS_3D_X, POS_3D_Y);
	mlx_put_image_to_window(
		data->mlx_ptr, data->win_ptr, minimap_img->img, POS_MAP_X, POS_MAP_Y);
	return (0);
}
