/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:02:43 by lorey             #+#    #+#             */
/*   Updated: 2025/06/03 01:51:08 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_ceiling_column(t_mlx_data *data, int x, t_3d_data *data_3d,
							t_data *selected)
{
	int				y;
	double			current_dist;
	double			ceil_x;
	double			ceil_y;

	y = -1;
	while (++y < data_3d->draw_start_y_clamped)
	{
		if (selected)
		{
			current_dist = (0.5 * TILE_SIZE * data_3d->dist_to_proj_plane)
				/ (SIZE_3D_IMG_Y / 2.0 - y);
			ceil_x = (data->player_x + data_3d->ray_dir_x * current_dist);
			ceil_y = data->player_y + data_3d->ray_dir_y * current_dist;
			my_mlx_pixel_put(data->img_ptr->game,
				SIZE_3D_IMG_X - x, y, get_texture_pixel(selected,
					(int)((ceil_x / TILE_SIZE - floor(ceil_x / TILE_SIZE))
						* selected->width), (int)((ceil_y / TILE_SIZE
							- floor(ceil_y / TILE_SIZE)) * selected->height)));
		}
		else
			my_mlx_pixel_put(data->img_ptr->game,
				SIZE_3D_IMG_X - x, y, data->rgb_data->ceiling_color);
	}
}

void	draw_ceiling_slice(t_mlx_data *data, int x, t_3d_data *data_3d)
{
	t_data			*selected_texture;

	selected_texture = NULL;
	if (!data->rgb)
	{
		selected_texture
			= data->img_arr->ceiling_img[(int)(((long long)data->frame_nbr
					* data->img_arr->ceiling_img[0]->frame_nbr) / FPS)];
		if (!selected_texture || !selected_texture->addr)
			return ;
	}
	render_ceiling_column(data, x, data_3d, selected_texture);
}

static void	render_floor_column(t_mlx_data *data, int x, t_3d_data *data_3d,
								t_data *selected)
{
	int				y;
	double			current_dist;
	double			floor_x;
	double			floor_y;

	y = data_3d->draw_end_y_clamped;
	while (y < (int)SIZE_3D_IMG_Y)
	{
		if (selected)
		{
			current_dist = (0.5 * TILE_SIZE * data_3d->dist_to_proj_plane)
				/ (y - SIZE_3D_IMG_Y / 2.0);
			floor_x = data->player_x + data_3d->ray_dir_x * current_dist;
			floor_y = data->player_y + data_3d->ray_dir_y * current_dist;
			my_mlx_pixel_put(data->img_ptr->game,
				SIZE_3D_IMG_X - x, y, get_texture_pixel(selected,
					(int)((floor_x / TILE_SIZE - floor(floor_x / TILE_SIZE))
						* selected->width), (int)((floor_y / TILE_SIZE
							- floor(floor_y / TILE_SIZE)) * selected->height)));
		}
		else
			my_mlx_pixel_put(data->img_ptr->game,
				SIZE_3D_IMG_X - x, y, data->rgb_data->floor_color);
		y++;
	}
}

void	draw_floor_slice(t_mlx_data *data, int x, t_3d_data *data_3d)
{
	t_data			*selected_texture;

	selected_texture = NULL;
	if (!data->rgb)
	{
		selected_texture
			= data->img_arr->floor_img[(int)(((long long)data->frame_nbr
					* data->img_arr->floor_img[0]->frame_nbr) / FPS)];
		if (!selected_texture || !selected_texture->addr)
			return ;
	}
	render_floor_column(data, x, data_3d, selected_texture);
}
