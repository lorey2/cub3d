/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <maambuhl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:48:07 by maambuhl          #+#    #+#             */
/*   Updated: 2025/04/25 17:03:37 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (true);
	return (false);
}

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
	return (true);
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
		if (pars_texture(split, data))
			NULL;
		else if (check_all_texture(data))
			break ;
	}
	return (i);
}
