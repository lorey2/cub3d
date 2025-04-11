/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <marcambuehl4@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:24:11 by maambuhl          #+#    #+#             */
/*   Updated: 2025/04/11 18:33:32 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (true);
	return (false);
}

char	*get_texture_value(char *line)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	j = 0;
	while (line[i + j] != '\n')
		j++;
	value = malloc(sizeof(char) * (j + 1));
	if (!value)
		err("Cannot allocate memory for texture value\n");
	j = 0;
	while (line[i + j] != '\n')
	{
		value[j] = line[i + j];
		j++;
	}
	value[j] = '\0';
	return (value);
}

void	check_texture(char **map, t_mlx_data *data)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == 'N' && map[i][1] == 'O' && ft_isspace(map[i][2]))
			data->texture->north = get_texture_value(map[i] + 2);
		else if (map[i][0] == 'S' && map[i][1] == 'O' && ft_isspace(map[i][2]))
			data->texture->south = get_texture_value(map[i] + 2);
		else if (map[i][0] == 'W' && map[i][1] == 'E' && ft_isspace(map[i][2]))
			data->texture->west = get_texture_value(map[i] + 2);
		else if (map[i][0] == 'E' && map[i][1] == 'A' && ft_isspace(map[i][2]))
			data->texture->east = get_texture_value(map[i] + 2);
		else if (map[i][0] == 'F' && ft_isspace(map[i][1]))
			data->texture->floor = get_texture_value(map[i] + 1);
		else if (map[i][0] == 'C' && ft_isspace(map[i][1]))
			data->texture->ceiling = get_texture_value(map[i] + 1);
		i++;
	}
}
