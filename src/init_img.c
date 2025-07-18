/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:24:54 by lorey             #+#    #+#             */
/*   Updated: 2025/06/09 15:40:47 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_img_error(t_mlx_data *data, t_data **img)
{
	write(1, "Error while trying to setup texture img\n", 40);
	write(1, "Probably the path is wrong in map\n", 34);
	safe_free((void **)img);
	free_everything(data);
	exit(1);
}

void	set_img(char **path, t_data ***img, t_mlx_data *data)
{
	int	nbr_frame;
	int	i;

	i = -1;
	nbr_frame = -1;
	while (path[++nbr_frame])
		;
	*img = malloc(sizeof(t_data *) * (nbr_frame + 1));
	i = -1;
	while (++i < nbr_frame)
	{
		(*img)[i] = malloc(sizeof(t_data));
		(*img)[i]->img = mlx_xpm_file_to_image(data->mlx_ptr,
				path[i],
				&(*img)[i]->width,
				&(*img)[i]->height);
		if (!((*img)[i]->img))
			set_img_error(data, &(*img)[i]);
		(*img)[i]->addr = mlx_get_data_addr((*img)[i]->img,
				&(*img)[i]->bits_per_pixel,
				&(*img)[i]->line_length,
				&(*img)[i]->endian);
	}
	(*img)[0]->frame_nbr = nbr_frame;
	(*img)[i] = NULL;
}

void	init_texture_image(t_mlx_data *data)
{
	if (data->text_arr->door_tex_name)
	{
		set_img(data->text_arr->door_tex_name,
			&data->img_arr->door_img, data);
	}
	if (!data->rgb)
	{
		set_img(data->text_arr->ceiling_tex_name,
			&data->img_arr->ceiling_img, data);
		set_img(data->text_arr->floor_tex_name,
			&data->img_arr->floor_img, data);
	}
	set_img(data->text_arr->west_tex_name,
		&data->img_arr->west_img, data);
	set_img(data->text_arr->east_tex_name,
		&data->img_arr->east_img, data);
	set_img(data->text_arr->north_tex_name,
		&data->img_arr->north_img, data);
	set_img(data->text_arr->south_tex_name,
		&data->img_arr->south_img, data);
}

void	setup_rgb(t_mlx_data *data)
{
	char	**ceil_split;
	char	**floor_split;

	if (data->rgb)
	{
		ceil_split = ft_split(data->text_arr->ceiling_tex_name[0], ',');
		data->rgb_data->ceiling_r = ft_atoi(ceil_split[0]);
		data->rgb_data->ceiling_g = ft_atoi(ceil_split[1]);
		data->rgb_data->ceiling_b = ft_atoi(ceil_split[2]);
		data->rgb_data->ceiling_color = (255 << 24
				| data->rgb_data->ceiling_r << 16
				| data->rgb_data->ceiling_g << 8
				| data->rgb_data->ceiling_b);
		multi_free(&ceil_split);
		floor_split = ft_split(data->text_arr->floor_tex_name[0], ',');
		data->rgb_data->floor_r = ft_atoi(floor_split[0]);
		data->rgb_data->floor_g = ft_atoi(floor_split[1]);
		data->rgb_data->floor_b = ft_atoi(floor_split[2]);
		data->rgb_data->floor_color = (255 << 24
				| data->rgb_data->floor_r << 16
				| data->rgb_data->floor_g << 8
				| data->rgb_data->floor_b);
		multi_free(&floor_split);
	}
}

void	init_img(t_mlx_data *data, t_img_ptr *img)
{
	data->img_arr = malloc(sizeof(t_tex_img_array));
	data->img_arr->north_img = NULL;
	data->img_arr->south_img = NULL;
	data->img_arr->east_img = NULL;
	data->img_arr->west_img = NULL;
	data->img_arr->ceiling_img = NULL;
	data->img_arr->floor_img = NULL;
	data->img_ptr->selected = NULL;
	data->img_arr->door_img = NULL;
	data->img_ptr->game = malloc(sizeof(t_data));
	data->img_ptr->minimap = malloc(sizeof(t_data));
	img->minimap->img = mlx_new_image(data->mlx_ptr,
			data->tile_y_nbr * TILE_SIZE * data->mm_ratio, data->y_size);
	img->minimap->addr = mlx_get_data_addr(img->minimap->img,
			&img->minimap->bits_per_pixel, &img->minimap->line_length,
			&img->minimap->endian);
	img->game->img = mlx_new_image(
			data->mlx_ptr, SIZE_3D_IMG_X, SIZE_3D_IMG_Y);
	init_texture_image(data);
	img->game->addr = mlx_get_data_addr(img->game->img,
			&img->game->bits_per_pixel, &img->game->line_length,
			&img->game->endian);
}
