/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <marcambuehl4@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:59:43 by maambuhl          #+#    #+#             */
/*   Updated: 2025/05/01 14:43:19 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_extension(char *map_file, t_mlx_data *data)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(map_file) - 1;
	if (map_file[len] != 'b' || map_file[len - 1] != 'u'
		|| map_file[len - 2] != 'c' || map_file[len - 3] != '.')
		err("Invalid map extentions", data);
	i = 0;
	if (i == (len - 3))
		err("You should provide a map name", data);
	while (i < (len - 3))
	{
		if (!ft_isprint(map_file[i++]))
			err("File name should contain only printable characters", data);
	}
}

int	count_mapfile_line(int fd, t_mlx_data *data)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	if (!line)
		err("Cannot get line", data);
	++i;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (free(line), i);
}

int	collect_texture(char **map, t_mlx_data *data)
{
	t_tex_name	*tex;
	int			line_to_remove;

	tex = malloc(sizeof(t_tex_name));
	if (!tex)
		err("Cannot allocate memory for texture\n", data);
	data->text_arr = tex;
	init_texture(tex);
	line_to_remove = check_texture(map, data);
	if (!check_all_texture(data))
		err("You should provide NO, SO, WE, EA, F and C texture\n", data);
	while (map[line_to_remove])
	{
		if (!check_line_sanity(map[line_to_remove]))
			line_to_remove++;
		break ;
	}
	multi_free(&map);
	return (line_to_remove);
}

void	parsing(char *map_file, t_mlx_data *data)
{
	char	**map;
	int		line;

	check_extension(map_file, data);
	map = load_map(map_file, data, 0);
	line = collect_texture(map, data);
	data->grid = load_map(map_file, data, line);
	remove_last_map_line(data);
	check_map(data);
}

char	**load_map(char *map_file, t_mlx_data *data, int line_to_rm)
{
	int		fd;
	int		nb_line;
	char	**grid;
	int		i;

	fd = open_helper(map_file, data);
	nb_line = count_mapfile_line(fd, data);
	close(fd);
	grid = malloc(sizeof(char *) * nb_line);
	if (!grid)
		err("Cannot allocate memory for map\n", data);
	fd = open_helper(map_file, data);
	i = 0;
	while (i < line_to_rm)
	{
		free(get_next_line(fd));
		line_to_rm--;
	}
	while (i < nb_line)
		grid[i++] = remove_line_return(get_next_line(fd));
	close(fd);
	return (grid);
}
