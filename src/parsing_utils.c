/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <maambuhl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:48:07 by maambuhl          #+#    #+#             */
/*   Updated: 2025/06/05 16:13:14 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_strisspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\v')
			i++;
		else
			break ;
	}
	if (str[i] == '\0')
		return (true);
	return (false);
}

char	*remove_line_return(char *line)
{
	int	len;

	if (line)
	{
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
		return (line);
	}
	return (line);
}

bool	check_all_texture(t_mlx_data *data)
{
	t_tex_name	*tex;

	tex = data->text_arr;
	if (!tex->ceiling_tex_name || !tex->floor_tex_name || !tex->east_tex_name
		|| !tex->north_tex_name || !tex->south_tex_name || !tex->west_tex_name)
		return (false);
	if (data->door && !tex->door_tex_name)
		return (false);
	return (true);
}

void	err_helper(t_mlx_data *data, char **map, char *str)
{
	multi_free(&map);
	err(str, data);
}

int	check_texture(char **map, t_mlx_data *data)
{
	int		i;
	char	**split;

	i = -1;
	while (map[++i])
	{
		split = ft_split(map[i], ' ');
		if (!split)
			err("Cannot split texture", data);
		if (pars_texture(split, data, map))
			NULL;
		else if (check_all_texture(data))
			break ;
	}
	if (!check_all_texture(data))
		err_helper(data, map, "You should provide NO, SO, WE, EA, F \
and C texture");
	if (!map[i])
		err_helper(data, map, "Map should be placed after texture \
declaration");
	while (!check_line_sanity(map[i]))
	{
		i++;
		if (!map[i])
			err_helper(data, map, "Map should be placed after texture \
declaration");
	}
	return (i);
}
