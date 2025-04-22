/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <marcambuehl4@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:59:43 by maambuhl          #+#    #+#             */
/*   Updated: 2025/04/22 15:44:47 by maambuhl         ###   LAUSANNE.ch       */
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

int	count_map_line(int fd, t_mlx_data *data)
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

void	parsing(char *map_file, t_mlx_data *data)
{
	check_extension(map_file, data);
	load_map(map_file, data);
}

void	collect_texture(char **map, t_mlx_data *data)
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
	remove_texture_from_map(map, line_to_remove, data);
}

void	load_map(char *map_file, t_mlx_data *data)
{
	int		fd;
	int		nb_line;
	char	**grid;
	int		i;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		err("Cannot open map file\n", data);
	nb_line = count_map_line(fd, data);
	close(fd);
	grid = malloc(sizeof(char *) * nb_line);
	if (!grid)
		err("Cannot allocate memory for map\n", data);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		err("Cannot open map file\n", data);
	i = 0;
	while (i < nb_line)
		grid[i++] = remove_line_return(get_next_line(fd));
	collect_texture(grid, data);
}
