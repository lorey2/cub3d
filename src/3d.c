/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:37:19 by lorey             #+#    #+#             */
/*   Updated: 2025/06/02 23:17:54 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_wall_slice(t_mlx_data *data, int x, t_3d_data *data_3d)
{
	int	y;
	int	color;

	y = data_3d->draw_start_y_clamped;
	data->start = data_3d->true_draw_start_y;
	while (y < data_3d->draw_end_y_clamped)
	{
		color = color_y(data, y, data_3d->proj_slice_height);
		my_mlx_pixel_put(data->img_ptr->game, SIZE_3D_IMG_X - x, y, color);
		y++;
	}
}

void	draw_3d(t_mlx_data *data, int x)
{
	data->data_3d->fov_rad_half = (FOV * M_PI / 180.0) / 2.0;
	calculate_wall_params(data, data->data_3d);
	calculate_draw_limits(data->data_3d);
	draw_wall_slice(data, x, data->data_3d);
	calculate_fc_ray_params(data, x, data->data_3d);
	draw_floor_slice(data, x, data->data_3d);
	draw_ceiling_slice(data, x, data->data_3d);
}
