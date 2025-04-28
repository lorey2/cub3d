/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:24:54 by lorey             #+#    #+#             */
/*   Updated: 2025/04/28 13:13:10 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	set_img(data->text_arr->ceiling_tex_name,
		&data->img_arr->ceiling_img, data);
	set_img(data->text_arr->west_tex_name,
		&data->img_arr->west_img, data);
	set_img(data->text_arr->floor_tex_name,
		&data->img_arr->floor_img, data);
	set_img(data->text_arr->east_tex_name,
		&data->img_arr->east_img, data);
	set_img(data->text_arr->north_tex_name,
		&data->img_arr->north_img, data);
	set_img(data->text_arr->south_tex_name,
		&data->img_arr->south_img, data);
}

void	init_img(t_mlx_data *data, t_img_ptr *img)
{
	init_texture_image(data);
	img->minimap->img = mlx_new_image(data->mlx_ptr, SIZE_MAP_X, data->y_size);
	img->minimap->addr = mlx_get_data_addr(img->minimap->img,
			&img->minimap->bits_per_pixel, &img->minimap->line_length,
			&img->minimap->endian);
	img->game->img = mlx_new_image(
			data->mlx_ptr, SIZE_3D_IMG_X, SIZE_3D_IMG_Y);
	img->game->addr = mlx_get_data_addr(img->game->img,
			&img->game->bits_per_pixel, &img->game->line_length,
			&img->game->endian);
}
