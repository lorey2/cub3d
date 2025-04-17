/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <maambuhl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:23:47 by maambuhl          #+#    #+#             */
/*   Updated: 2025/04/17 17:04:00 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	multi_free(void ***data)
{
	int	i;

	i = 0;
	if (*data)
	{
		while ((*data)[i])
		{
			safe_free((*data + i));
			i++;
		}
		safe_free((void **)data);
	}
}

void	free_texture(t_mlx_data *data)
{
	multi_free((void ***)&data->text_arr->north_tex_name);
	multi_free((void ***)&data->text_arr->south_tex_name);
	multi_free((void ***)&data->text_arr->west_tex_name);
	multi_free((void ***)&data->text_arr->east_tex_name);
	multi_free((void ***)&data->text_arr->floor_tex_name);
	multi_free((void ***)&data->text_arr->ceiling_tex_name);
	multi_free((void ***)&data->text_arr->door_tex_name);
}

void	free_everything(t_mlx_data *data)
{
	free_texture(data);
	multi_free((void ***)&data->grid);
}
