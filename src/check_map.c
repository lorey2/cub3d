/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <maambuhl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:14:08 by maambuhl          #+#    #+#             */
/*   Updated: 2025/05/01 14:14:10 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_test(char **map, int y, int x, int nb_line, bool *check)
{
	if (map[y][x] == ' ')
	{
		*check = false;
		return ;
	}
	map[y][x] = 'X';
	if (x < (int)ft_strlen(map[y]) - 1 && !check_wall(map[y][x + 1]))
		wall_test(map, y, x + 1, nb_line, check);
	if (y > 0 && !check_wall(map[y - 1][x]))
		wall_test(map, y - 1, x, nb_line, check);
	if (x > 0 && !check_wall(map[y][x - 1]))
		wall_test(map, y, x - 1, nb_line, check);
	if (y < nb_line - 1 && !check_wall(map[y + 1][x]))
		wall_test(map, y + 1, x, nb_line, check);
}

void	make_map_square(t_mlx_data *data)
{
	size_t	longest_line;
	size_t	len;
	char	*padding;
	char	*new_line;
	int		i;

	longest_line = get_longest_line(data);
	i = 0;
	while (data->grid[i])
	{
		len = ft_strlen(data->grid[i]);
		if (len < longest_line)
		{
			padding = create_padding_string(longest_line - len, data);
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
	char	**map_copy;
	int		yx[2];
	bool	wall;

	check_map_content(data);
	make_map_square(data);
	map_copy = copy_map(data);
	wall = true;
	while (get_blank_space(map_copy, yx))
		wall_test(map_copy, yx[0], yx[1], count_map_line(data), &wall);
	multi_free(&map_copy);
	if (!wall)
		err("The map should be surrounded by walls", data);
}
