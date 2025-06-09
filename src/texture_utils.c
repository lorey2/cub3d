/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <maambuhl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:58:12 by maambuhl          #+#    #+#             */
/*   Updated: 2025/06/09 15:55:38 by maambuhl         ###   LAUSANNE.ch       */
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

bool	count_rgb(char **f_split, char **c_split)
{
	int	i;

	i = 0;
	while (f_split[i])
		i++;
	if (i != 3)
		return (false);
	i = 0;
	while (c_split[i])
		i++;
	if (i != 3)
		return (false);
	return (true);
}

bool	pars_texture(char **split, t_mlx_data *data, char **map)
{
	if (ft_isequal(split[0], "NO") && !data->text_arr->north_tex_name)
		data->text_arr->north_tex_name = copy_texture(split);
	else if (ft_isequal(split[0], "SO") && !data->text_arr->south_tex_name)
		data->text_arr->south_tex_name = copy_texture(split);
	else if (ft_isequal(split[0], "WE") && !data->text_arr->west_tex_name)
		data->text_arr->west_tex_name = copy_texture(split);
	else if (ft_isequal(split[0], "EA") && !data->text_arr->east_tex_name)
		data->text_arr->east_tex_name = copy_texture(split);
	else if (ft_isequal(split[0], "F") && !data->text_arr->floor_tex_name)
		data->text_arr->floor_tex_name = copy_texture(split);
	else if (ft_isequal(split[0], "C") && !data->text_arr->ceiling_tex_name)
		data->text_arr->ceiling_tex_name = copy_texture(split);
	else if (ft_isequal(split[0], "D") && !data->text_arr->door_tex_name)
		data->text_arr->door_tex_name = copy_texture(split);
	else
		return (pars_texture_helper_utils(split, map, data),
			multi_free(&split), false);
	multi_free(&split);
	return (true);
}

bool	check_rgb_digit(char **f_split, char **c_split)
{
	int	i;

	i = 0;
	while (f_split[i])
	{
		if (!ft_strisdigit(f_split[i])
			|| ft_atoi(f_split[i]) > 255 || ft_atoi(f_split[i]) < 0)
			return (multi_free(&f_split), multi_free(&c_split), false);
		i++;
	}
	i = 0;
	while (c_split[i])
	{
		if (!ft_strisdigit(c_split[i])
			|| ft_atoi(c_split[i]) > 255 || ft_atoi(c_split[i]) < 0)
			return (multi_free(&f_split), multi_free(&c_split), false);
		i++;
	}
	return (true);
}

void	check_rgb(t_mlx_data *data)
{
	char	**f_split;
	char	**c_split;

	if (!data->text_arr->ceiling_tex_name[0]
		|| !data->text_arr->floor_tex_name[0]
		|| data->text_arr->ceiling_tex_name[1]
		|| data->text_arr->floor_tex_name[1])
		return ;
	f_split = ft_split(data->text_arr->floor_tex_name[0], ',');
	c_split = ft_split(data->text_arr->ceiling_tex_name[0], ',');
	if (!f_split || !c_split)
		return ;
	if (!count_rgb(f_split, c_split))
	{
		multi_free(&f_split);
		multi_free(&c_split);
		return ;
	}
	if (!check_rgb_digit(f_split, c_split))
		return ;
	multi_free(&f_split);
	multi_free(&c_split);
	data->rgb = true;
}
