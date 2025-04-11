/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <marcambuehl4@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:59:43 by maambuhl          #+#    #+#             */
/*   Updated: 2025/04/11 18:38:33 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_extension(char *map_file)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(map_file) - 1;
	if (map_file[len] != 'b' || map_file[len - 1] != 'u'
		|| map_file[len - 2] != 'c' || map_file[len - 3] != '.')
		err("Invalid map extentions");
	i = 0;
	if (i == (len - 3))
		err("You should provide a map name");
	while (i < (len - 3))
	{
		if (!ft_isprint(map_file[i++]))
			err("File name should contain only printable characters");
	}
}

int	count_map_line(int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	if (!line)
		return (safe_free((void **)&line), i);
	++i;
	while (line)
	{
		safe_free((void **)&line);
		line = get_next_line(fd);
		i++;
	}
	return (safe_free((void **)&line), i);
}

void	check_map(char *map_file, t_mlx_data *data)
{
	check_extension(map_file);
	load_map(map_file, data);
}

void	collect_texture(char **map, t_mlx_data *data)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		err("Cannot allocate memory for texture\n");
	data->texture = texture;
	check_texture(map, data);
	if (!texture->ceiling ||!texture->floor || !texture->east
		|| !texture->north || !texture->south || !texture->west)
	{
		err("You should provide NO, SO, WE, EA, F and C texture\n");
	}
}

void	load_map(char *map_file, t_mlx_data *data)
{
	int		fd;
	int		nb_line;
	char	**grid;
	int		i;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		err("Cannot open map file\n");
	nb_line = count_map_line(fd);
	close(fd);
	grid = malloc(sizeof(char *) * nb_line);
	if (!grid)
		err("Cannot allocate memory for map\n");
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		err("Cannot open map file\n");
	i = 0;
	while (i < nb_line)
		grid[i++] = get_next_line(fd);
	collect_texture(grid, data);
}
