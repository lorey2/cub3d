/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:14:44 by lorey             #+#    #+#             */
/*   Updated: 2025/06/02 23:15:42 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_slice(t_mlx_data *data, int x, t_3d_data *data_3d)
{
	int		y;
	double	current_dist;
	double	floor_x;
	double	floor_y;
	t_data	*selected;

	if (!data->rgb)
	{
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
	else
	{
		y = data_3d->draw_end_y_clamped;
		while (y < (int)SIZE_3D_IMG_Y)
		{
			my_mlx_pixel_put(data->img_ptr->game, SIZE_3D_IMG_X - x, y,
				data->rgb_data->floor_color);
			y++;
		}
	}
}

void	draw_ceiling_slice(t_mlx_data *data, int x, t_3d_data *data_3d)
{
	int		y;
	double	current_dist;
	double	ceil_x;
	double	ceil_y;
	t_data	*selected;

	if (!data->rgb)
	{
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
	else
	{
		y = 0;
		while (y < data_3d->draw_start_y_clamped)
		{
			my_mlx_pixel_put(data->img_ptr->game, SIZE_3D_IMG_X - x, y,
				data->rgb_data->ceiling_color);
			y++;
		}
	}
}
