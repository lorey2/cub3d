/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <maambuhl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:23:47 by maambuhl          #+#    #+#             */
/*   Updated: 2025/04/28 18:42:51 by lorey            ###   LAUSANNE.ch       */
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

void	free_texture(t_mlx_data *data)
{
	int	i;

	i = -1;
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
		mlx_destroy_image(data->mlx_ptr, data->img_ptr->minimap->img);
		safe_free((void *)&data->img_ptr->minimap);
//		mlx_destroy_image(data->mlx_ptr, data->img_ptr->selected->img);
//		safe_free((void *)&data->img_ptr->selected);
		safe_free((void *)&data->img_ptr);
	}
	if (data->img_arr)
	{
		i = -1;
		while (data->img_arr->ceiling_img[++i] != NULL)
		{
			mlx_destroy_image(data->mlx_ptr, data->img_arr->ceiling_img[i]->img);
			safe_free((void *)&data->img_arr->ceiling_img[i]);
		}
		safe_free((void *)&data->img_arr->ceiling_img);
		i = -1;
		while (data->img_arr->floor_img[++i])
		{
			mlx_destroy_image(data->mlx_ptr, data->img_arr->floor_img[i]->img);
			safe_free((void *)&data->img_arr->floor_img[i]);
		}
		safe_free((void *)&data->img_arr->floor_img);
		i = -1;
		while (data->img_arr->north_img[++i])
		{
			mlx_destroy_image(data->mlx_ptr, data->img_arr->north_img[i]->img);
			safe_free((void *)&data->img_arr->north_img[i]);
		}
		safe_free((void *)&data->img_arr->north_img);
		i = -1;
		while (data->img_arr->south_img[++i])
		{
			mlx_destroy_image(data->mlx_ptr, data->img_arr->south_img[i]->img);
			safe_free((void *)&data->img_arr->south_img[i]);
		}
		safe_free((void *)&data->img_arr->south_img);
		i = -1;
		while (data->img_arr->east_img[++i])
		{
			mlx_destroy_image(data->mlx_ptr, data->img_arr->east_img[i]->img);
			safe_free((void *)&data->img_arr->east_img[i]);
		}
		safe_free((void *)&data->img_arr->east_img);
		i = -1;
		while (data->img_arr->west_img[++i])
		{
			mlx_destroy_image(data->mlx_ptr, data->img_arr->west_img[i]->img);
			safe_free((void *)&data->img_arr->west_img[i]);
		}
		safe_free((void *)&data->img_arr->west_img);
		i = -1;
		while (data->img_arr->door_img[++i])
		{
			mlx_destroy_image(data->mlx_ptr, data->img_arr->door_img[i]->img);
			safe_free((void *)&data->img_arr->door_img[i]);
		}
		safe_free((void *)&data->img_arr->door_img);
		safe_free((void *)&data->img_arr);
	}
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
