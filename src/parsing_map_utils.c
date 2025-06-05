/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <marcambuehl4@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:01:04 by maambuhl          #+#    #+#             */
/*   Updated: 2025/06/05 15:37:08 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*create_padding_string(size_t size, t_mlx_data *data)
{
	char	*str;
	size_t	i;

	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		err("Cannot allocate memory for padding string", data);
	i = 0;
	while (i < size)
		str[i++] = ' ';
	str[i] = '\0';
	return (str);
}

char	**copy_map(t_mlx_data *data)
{
	char	**map_copy;
	int		map_line;
	int		i;

	map_line = count_map_line(data);
	map_copy = malloc(sizeof(char *) * (map_line + 1));
	if (!map_copy)
		err("Cannot allocate memory to copy map", data);
	i = 0;
	while (i < map_line)
	{
		map_copy[i] = ft_strdup(data->grid[i]);
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

int	*get_blank_space(char **map, int *yx)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' || map[y][x] == 'W' || map[y][x] == 'N'
			|| map[y][x] == 'S' || map[y][x] == 'E')
				return (yx[0] = y, yx[1] = x, yx);
			x++;
		}
		y++;
	}
	return (NULL);
}

bool	valid_map_char(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'X'
		&& c != 'E' && c != 'W' && c != 'D' && c != ' ')
		return (false);
	return (true);
}

bool	check_wall(char c)
{
	if (c == '1' || c == 'X')
		return (true);
	return (false);
}
