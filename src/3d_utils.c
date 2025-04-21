/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:34:53 by lorey             #+#    #+#             */
/*   Updated: 2025/04/21 20:39:01 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_y(t_mlx_data *data, int index, double proj_slice_height)
{
	int		x;
	int		y;
	int		color;
	int		pixel_index;
	double	ratio;

	if (!data->img_ptr->selected)
		return (0);
	x = data->textu_x;
	ratio = (double)(index - data->start) / proj_slice_height;
	y = ratio * data->img_ptr->selected->height;
	if (y < 0)
		y = 0;
	if (y >= data->img_ptr->selected->height)
		y = data->img_ptr->selected->height - 1;
	pixel_index = y * data->img_ptr->selected->line_length + x
		* (data->img_ptr->selected->bits_per_pixel / 8);
	color = *(int *)(data->img_ptr->selected->addr + pixel_index);
	return (color);
}

int	get_texture_pixel(t_data *texture, int tex_x, int tex_y)
{
	char	*pixel_addr;
	int		color;

	if (!texture || !texture->addr)
		return (BLACK);
	tex_x = tex_x % texture->width;
	tex_y = tex_y % texture->height;
	if (tex_x < 0)
		tex_x += texture->width;
	if (tex_y < 0)
		tex_y += texture->height;
	if (tex_x < 0 || tex_x >= texture->width || \
		tex_y < 0 || tex_y >= texture->height)
		return (BLACK);
	pixel_addr = texture->addr + (tex_y * texture->line_length + \
		tex_x * (texture->bits_per_pixel / 8));
	color = *(int *)pixel_addr;
	return (color);
}

void	calculate_wall_params(t_mlx_data *data, t_3d_data *data_3d)
{
	data_3d->perp_dist = data->best * cos(data->angle - data->angle_bkp);
	if (data_3d->perp_dist < 0.0001)
		data_3d->perp_dist = 0.0001;
	if (fabs(tan(data_3d->fov_rad_half)) < TOLERANCE)
		data_3d->dist_to_proj_plane = 1.0 / TOLERANCE;
	else
		data_3d->dist_to_proj_plane = (SIZE_3D_IMG_X / 2.0)
			/ tan(data_3d->fov_rad_half);
	data_3d->proj_slice_height = (TILE_SIZE / data_3d->perp_dist)
		* data_3d->dist_to_proj_plane;
}

void	calculate_draw_limits(t_3d_data *data_3d)
{
	data_3d->draw_start_y_clamped = (int)(SIZE_3D_IMG_Y / 2.0
			- data_3d->proj_slice_height / 2.0);
	data_3d->draw_end_y_clamped = (int)(SIZE_3D_IMG_Y / 2.0
			+ data_3d->proj_slice_height / 2.0);
	data_3d->true_draw_start_y = data_3d->draw_start_y_clamped;
	if (data_3d->draw_start_y_clamped < 0)
		data_3d->draw_start_y_clamped = 0;
	if (data_3d->draw_end_y_clamped >= (int)SIZE_3D_IMG_Y)
		data_3d->draw_end_y_clamped = (int)SIZE_3D_IMG_Y;
}

void	calculate_fc_ray_params(t_mlx_data *data, int x, t_3d_data *data_3d)
{
	double	player_dir_x;
	double	player_dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;

	player_dir_x = cos(data->angle_bkp);
	player_dir_y = sin(data->angle_bkp);
	plane_x = -player_dir_y * tan(data_3d->fov_rad_half);
	plane_y = player_dir_x * tan(data_3d->fov_rad_half);
	camera_x = 2.0 * x / SIZE_3D_IMG_X - 1.0;
	data_3d->ray_dir_x = player_dir_x + plane_x * camera_x;
	data_3d->ray_dir_y = player_dir_y + plane_y * camera_x;
}
