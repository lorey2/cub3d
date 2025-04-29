/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <maambuhl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:58:12 by maambuhl          #+#    #+#             */
/*   Updated: 2025/04/29 15:58:29 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**copy_texture(char **split)
{
	int		len;
	char	**tex;
	int		i;

	len = 0;
	while (split[len])
		len++;
	tex = malloc(sizeof(char *) * len);
	i = 0;
	while ((i + 1) < len)
	{
		tex[i] = ft_strdup(split[i + 1]);
		i++;
	}
	tex[i] = NULL;
	return (tex);
}

void	print_map(t_mlx_data *data)
{
	int	i;

	i = 0;
	while (data->grid[i])
		printf("%s\n", data->grid[i++]);
}

bool	pars_texture(char **split, t_mlx_data *data)
{
	if (ft_isequal(split[0], "NO"))
		data->text_arr->north_tex_name = copy_texture(split);
	else if (ft_isequal(split[0], "SO"))
		data->text_arr->south_tex_name = copy_texture(split);
	else if (ft_isequal(split[0], "WE"))
		data->text_arr->west_tex_name = copy_texture(split);
	else if (ft_isequal(split[0], "EA"))
		data->text_arr->east_tex_name = copy_texture(split);
	else if (ft_isequal(split[0], "F"))
		data->text_arr->floor_tex_name = copy_texture(split);
	else if (ft_isequal(split[0], "C"))
		data->text_arr->ceiling_tex_name = copy_texture(split);
	else if (ft_isequal(split[0], "D"))
		data->text_arr->door_tex_name = copy_texture(split);
	else
	{
		multi_free(&split);
		return (false);
	}
	multi_free(&split);
	return (true);
}
