/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:41:56 by lorey             #+#    #+#             */
/*   Updated: 2025/04/09 15:22:18 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define SCREEN_WIDTH S_RAY_X
#define SCREEN_HEIGHT S_RAY_Y
#define ACTUAL_WALL_HEIGHT TILE_SIZE

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

void	draw_3d(t_mlx_data *data, int ray_index)
{
	double	perp_dist;
	double	dist_to_proj_plane;
	double	proj_slice_height;
	int		draw_start_y;
	int		draw_end_y;

	perp_dist = data->best * cos(data->angle - data->angle_bkp);
	if (perp_dist < 0.0001)
		perp_dist = 0.0001;
	if (fabs(tan(FOV * M_PI / 180 / 2.0)) < 0.0001)
		dist_to_proj_plane = 10000.0;
	else
		dist_to_proj_plane = (SCREEN_WIDTH / 2.0) / tan(FOV * M_PI / 180 / 2.0);
	proj_slice_height = (ACTUAL_WALL_HEIGHT / perp_dist) * dist_to_proj_plane;
	draw_start_y = SCREEN_HEIGHT / 2 - (int)(proj_slice_height / 2.0);
	draw_end_y = SCREEN_HEIGHT / 2 + (int)(proj_slice_height / 2.0);
	if (draw_start_y < 0)
		draw_start_y = 0;
	if (draw_end_y > SCREEN_HEIGHT)
		draw_end_y = SCREEN_HEIGHT;
	if (ray_index >= 0 && ray_index < SCREEN_WIDTH)
		while (draw_start_y++ < draw_end_y)
			my_mlx_pixel_put(&(*data->raycast),
				ray_index, draw_start_y, data->color);
}
