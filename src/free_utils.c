/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:10:23 by lorey             #+#    #+#             */
/*   Updated: 2025/04/29 14:06:15 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	multi_free(char ***point)
{
	int	j;

	j = -1;
	if (*point)
	{
		while ((*point)[++j])
			safe_free((void **)&(*point)[j]);
		safe_free((void **)point);
	}
}

void	free_texture_array(t_data ***img_arr, void *mlx_ptr)
{
	int	i;

	if (img_arr == NULL || *img_arr == NULL)
	{
		return ;
	}
	i = -1;
	while ((*img_arr)[++i] != NULL)
	{
		if ((*img_arr)[i])
		{
			if ((*img_arr)[i]->img)
			{
				mlx_destroy_image(mlx_ptr, (*img_arr)[i]->img);
			}
			safe_free((void **)&((*img_arr)[i]));
		}
	}
	safe_free((void **)img_arr);
}

void	free_img_array(t_mlx_data *data)
{
	if (data->img_arr)
	{
		free_texture_array(&data->img_arr->ceiling_img, data->mlx_ptr);
		free_texture_array(&data->img_arr->floor_img, data->mlx_ptr);
		free_texture_array(&data->img_arr->north_img, data->mlx_ptr);
		free_texture_array(&data->img_arr->south_img, data->mlx_ptr);
		free_texture_array(&data->img_arr->east_img, data->mlx_ptr);
		free_texture_array(&data->img_arr->west_img, data->mlx_ptr);
		free_texture_array(&data->img_arr->door_img, data->mlx_ptr);
		safe_free((void *)&data->img_arr);
	}
}

void	free_texture(t_mlx_data *data)
{
	multi_free(&data->text_arr->north_tex_name);
	multi_free(&data->text_arr->south_tex_name);
	multi_free(&data->text_arr->west_tex_name);
	multi_free(&data->text_arr->east_tex_name);
	multi_free(&data->text_arr->floor_tex_name);
	multi_free(&data->text_arr->ceiling_tex_name);
	multi_free(&data->text_arr->door_tex_name);
	multi_free(&data->grid);
	safe_free((void *)&data->text_arr);
	if (data->img_ptr)
	{

		mlx_destroy_image(data->mlx_ptr, data->img_ptr->game->img);
		safe_free((void *)&data->img_ptr->game);
		write(1, "YO\n", 3);
		mlx_destroy_image(data->mlx_ptr, data->img_ptr->minimap->img);
		safe_free((void *)&data->img_ptr->minimap);
		safe_free((void *)&data->img_ptr);
	}
	free_img_array(data);
}

void	free_everything(t_mlx_data *data)
{
	free_texture(data);
	multi_free(&data->grid);
	safe_free((void *)&data->key);
	safe_free((void *)&data->l);
	safe_free((void *)&data->data_3d);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	safe_free((void *)&data->mlx_ptr);
}
