/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:37:19 by lorey             #+#    #+#             */
/*   Updated: 2025/04/21 19:49:34 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//static void	calculate_draw_limits(double p_height, \
//				int *ds_clamped, int *de_clamped, int *true_ds);
static void	draw_wall_slice(t_mlx_data *data, int x, int ds_clamped, \
				int de_clamped, double p_height, int true_ds);
static void	calculate_fc_ray_params(t_mlx_data *data, int x, \
				double *ray_dx, double *ray_dy, double fov_rad_h);
static void	draw_floor_slice(t_mlx_data *data, int x, int de_clamped, \
				double ray_dx, double ray_dy, double d_plane);
static void	draw_ceiling_slice(t_mlx_data *data, int x, int ds_clamped, \
				double ray_dx, double ray_dy, double d_plane);

int color_y(t_mlx_data *data, int index, double proj_slice_height)
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

static void	calculate_wall_params(t_mlx_data *data, t_3d_data *data_3d)
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

static void	calculate_draw_limits(t_3d_data *data_3d)
{
	data_3d->draw_start_y_clamped = (int)(SIZE_3D_IMG_Y / 2.0 - data_3d->proj_slice_height / 2.0);
	data_3d->draw_end_y_clamped = (int)(SIZE_3D_IMG_Y / 2.0 + data_3d->proj_slice_height / 2.0);
	data_3d->true_draw_start_y = data_3d->draw_start_y_clamped;
	if (data_3d->draw_start_y_clamped < 0)
		data_3d->draw_start_y_clamped = 0;
	if (data_3d->draw_end_y_clamped >= (int)SIZE_3D_IMG_Y)
		data_3d->draw_end_y_clamped = (int)SIZE_3D_IMG_Y;
}

static void	draw_wall_slice(t_mlx_data *data, int x, int ds_clamped, \
					int de_clamped, double p_height, int true_ds)
{
	int	y;
	int	color;

	y = ds_clamped;
	data->start = true_ds;
	while (y < de_clamped)
	{
		color = color_y(data, y, p_height);
		my_mlx_pixel_put(data->img_ptr->game, x, y, color);
		y++;
	}
}

static void	calculate_fc_ray_params(t_mlx_data *data, int x, \
						double *ray_dx, double *ray_dy, double fov_rad_h)
{
	double	player_dir_x;
	double	player_dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;

	player_dir_x = cos(data->angle_bkp);
	player_dir_y = sin(data->angle_bkp);
	plane_x = -player_dir_y * tan(fov_rad_h);
	plane_y = player_dir_x * tan(fov_rad_h);
	camera_x = 2.0 * x / SIZE_3D_IMG_X - 1.0;
	*ray_dx = player_dir_x + plane_x * camera_x;
	*ray_dy = player_dir_y + plane_y * camera_x;
}

static void	draw_floor_slice(t_mlx_data *data, int x, int de_clamped, \
							double ray_dx, double ray_dy, double d_plane)
{
	int		y;
	double	current_dist;
	double	floor_x;
	double	floor_y;
	int		tex_x;
	int		tex_y;
	int		floor_color;
	t_data	*selected;

	selected = data->img_arr->floor_img[(int)(((long long)data->frame_nbr * data->img_arr->floor_img[0]->frame_nbr) / FPS)];
	if (!selected || !selected->addr)
		return ;
	y = de_clamped;
	while (y < (int)SIZE_3D_IMG_Y)
	{
		current_dist = (0.5 * TILE_SIZE * d_plane) / (y - SIZE_3D_IMG_Y / 2.0);
		floor_x = data->player_x + ray_dx * current_dist;
		floor_y = data->player_y + ray_dy * current_dist;
		tex_x = (int)((floor_x / TILE_SIZE - floor(floor_x / TILE_SIZE)) * \
				selected->width);
		tex_y = (int)((floor_y / TILE_SIZE - floor(floor_y / TILE_SIZE)) * \
				selected->height);
		floor_color = get_texture_pixel(selected, tex_x, tex_y);
		my_mlx_pixel_put(data->img_ptr->game, x, y, floor_color);
		y++;
	}
}

static void	draw_ceiling_slice(t_mlx_data *data, int x, int ds_clamped, \
								double ray_dx, double ray_dy, double d_plane)
{
	int		y;
	double	current_dist;
	double	ceil_x;
	double	ceil_y;
	int		tex_x;
	int		tex_y;
	int		ceil_color;
	t_data	*selected;

	selected = data->img_arr->ceiling_img[(int)(((long long)data->frame_nbr * data->img_arr->ceiling_img[0]->frame_nbr) / FPS)];
	if (!selected || !selected->addr)
		return ;
	y = 0;
	while (y < ds_clamped)
	{
		current_dist = (0.5 * TILE_SIZE * d_plane) / (SIZE_3D_IMG_Y / 2.0 - y);
		ceil_x = data->player_x + ray_dx * current_dist;
		ceil_y = data->player_y + ray_dy * current_dist;
		tex_x = (int)((ceil_x / TILE_SIZE - floor(ceil_x / TILE_SIZE)) * \
				selected->width);
		tex_y = (int)((ceil_y / TILE_SIZE - floor(ceil_y / TILE_SIZE)) * \
				selected->height);
		ceil_color = get_texture_pixel(selected, tex_x, tex_y);
		my_mlx_pixel_put(data->img_ptr->game, x, y, ceil_color);
		y++;
	}
}

void draw_3d(t_mlx_data *data, int x)
{
	data->data_3d->fov_rad_half = (FOV * M_PI / 180.0) / 2.0;
	calculate_wall_params(data, data->data_3d);
	calculate_draw_limits(data->data_3d);
	draw_wall_slice(data, x, data->data_3d->draw_start_y_clamped, data->data_3d->draw_end_y_clamped, \
					data->data_3d->proj_slice_height, data->data_3d->true_draw_start_y);
	calculate_fc_ray_params(data, x, &data->data_3d->ray_dir_x, &data->data_3d->ray_dir_y, data->data_3d->fov_rad_half);
	draw_floor_slice(data, x, data->data_3d->draw_end_y_clamped, data->data_3d->ray_dir_x, data->data_3d->ray_dir_y, \
					data->data_3d->dist_to_proj_plane);
	draw_ceiling_slice(data, x, data->data_3d->draw_start_y_clamped, data->data_3d->ray_dir_x, data->data_3d->ray_dir_y, \
					data->data_3d->dist_to_proj_plane);
}
