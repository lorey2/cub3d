/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <maambuhl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:14:08 by maambuhl          #+#    #+#             */
/*   Updated: 2025/04/24 13:49:11 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void	wall_test(t_mlx_data *data)
{
} */

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

void	make_map_square(t_mlx_data *data)
{
	size_t	longest_line;
	size_t	len;
	size_t	diff;
	char	*padding;
	char	*new_line;

	int	i;

	longest_line = 0;
	i = 0;
	while (data->grid[i])
	{
		len = ft_strlen(data->grid[i++]);
		if (len > longest_line)
			longest_line = len;
	}
	i = 0;
	while (data->grid[i])
	{
		len = ft_strlen(data->grid[i]);
		if (len < longest_line)
		{
			diff = longest_line - len;
			padding = create_padding_string(diff, data);
			new_line = ft_strjoin(data->grid[i], padding);
			safe_free((void **)&data->grid[i]);
			safe_free((void **)&padding);
			data->grid[i] = new_line;
		}
		i++;
	}
}

void	check_map_content(t_mlx_data *data)
{
	int		i;
	int		y;
	char	c;
	int		player;

	i = 0;
	player = 0;
	while (data->grid[i])
	{
		y = 0;
		while (data->grid[i][y])
		{
			c = data->grid[i][y];
			if (c != '0' && c != '1' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W' && c != 'D' && c != ' ')
				err("Map must contain only: 0, 1, N, S, E, W, D, ' '", data);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				player++;
			y++;
		}
		i++;
	}
	if (player != 1)
		err("You should provide one player position on the map", data);
}

void	check_map(t_mlx_data *data)
{
	check_map_content(data);
	make_map_square(data);
	// wall_test(data);
}
