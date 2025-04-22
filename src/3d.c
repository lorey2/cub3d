/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:37:19 by lorey             #+#    #+#             */
/*   Updated: 2025/04/22 05:32:16 by lorey            ###   LAUSANNE.ch       */
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

static void	draw_floor_slice(t_mlx_data *data, int x, t_3d_data *data_3d)
{
	int		y;
	double	current_dist;
	double	floor_x;
	double	floor_y;
	t_data	*selected;

	selected = data->img_arr->floor_img[(int)(((long long)data->frame_nbr
				* data->img_arr->floor_img[0]->frame_nbr) / FPS)];
	if (!selected || !selected->addr)
		return ;
	y = data_3d->draw_end_y_clamped;
	while (y < (int)SIZE_3D_IMG_Y)
	{
		current_dist = (0.5 * TILE_SIZE * data_3d->dist_to_proj_plane)
			/ (y - SIZE_3D_IMG_Y / 2.0);
		floor_x = data->player_x + data_3d->ray_dir_x * current_dist;
		floor_y = data->player_y + data_3d->ray_dir_y * current_dist;
		my_mlx_pixel_put(data->img_ptr->game, SIZE_3D_IMG_X - x, y,
			get_texture_pixel(selected,
				(int)((floor_x / TILE_SIZE
						- floor(floor_x / TILE_SIZE)) * selected->width),
				(int)((floor_y / TILE_SIZE
						- floor(floor_y / TILE_SIZE)) * selected->height)));
		y++;
	}
}

static void	draw_ceiling_slice(t_mlx_data *data, int x, t_3d_data *data_3d)
{
	int		y;
	double	current_dist;
	double	ceil_x;
	double	ceil_y;
	t_data	*selected;

	selected = data->img_arr->ceiling_img[(int)(((long long)data->frame_nbr
				* data->img_arr->ceiling_img[0]->frame_nbr) / FPS)];
	if (!selected || !selected->addr)
		return ;
	y = 0;
	while (y < data_3d->draw_start_y_clamped)
	{
		current_dist = (0.5 * TILE_SIZE * data_3d->dist_to_proj_plane)
			/ (SIZE_3D_IMG_Y / 2.0 - y);
		ceil_x = data->player_x + data_3d->ray_dir_x * current_dist;
		ceil_y = data->player_y + data_3d->ray_dir_y * current_dist;
		my_mlx_pixel_put(data->img_ptr->game, SIZE_3D_IMG_X - x, y,
			get_texture_pixel(selected,
				(int)((ceil_x / TILE_SIZE
						- floor(ceil_x / TILE_SIZE)) * selected->width),
				(int)((ceil_y / TILE_SIZE
						- floor(ceil_y / TILE_SIZE)) * selected->height)));
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
