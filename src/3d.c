/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:37:32 by lorey             #+#    #+#             */
/*   Updated: 2025/04/07 21:29:21 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define SCREEN_WIDTH S_RAY_X
#define SCREEN_HEIGHT S_RAY_Y
#define FOV_DEGREES 60.0
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

void draw_3d(t_mlx_data *data, int ray_index)
{
    double perpendicular_distance;
    double distance_to_projection_plane;
    double projected_slice_height;
    double fov_radians = FOV_DEGREES * M_PI / 180.0;
    int screen_center_y = SCREEN_HEIGHT / 2;
    int draw_start_y;
    int draw_end_y;
    int screen_x;
    perpendicular_distance = data->best * cos(data->angle - data->angle_bkp);
    if (perpendicular_distance < 0.0001)
        perpendicular_distance = 0.0001;
    double tan_half_fov = tan(fov_radians / 2.0);
    if (fabs(tan_half_fov) < 0.0001) 
         distance_to_projection_plane = 10000.0;
    else
         distance_to_projection_plane = (SCREEN_WIDTH / 2.0) / tan_half_fov;
    projected_slice_height = (ACTUAL_WALL_HEIGHT / perpendicular_distance) * distance_to_projection_plane;
    int calculated_half_height = (int)(projected_slice_height / 2.0);
    draw_start_y = screen_center_y - calculated_half_height;
    draw_end_y = screen_center_y + calculated_half_height;
    if (draw_start_y < 0)
        draw_start_y = 0;
    if (draw_end_y > SCREEN_HEIGHT)
        draw_end_y = SCREEN_HEIGHT;
    screen_x = ray_index;
    if (screen_x >= 0 && screen_x < SCREEN_WIDTH)
        for (int y = draw_start_y; y < draw_end_y; y++)
            my_mlx_pixel_put(&(*data->raycast), screen_x, y, data->color);
}
