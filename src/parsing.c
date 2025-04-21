/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <marcambuehl4@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:59:43 by maambuhl          #+#    #+#             */
/*   Updated: 2025/04/21 18:20:30 by lorey            ###   LAUSANNE.ch       */
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
		err("Cannot get line");
	++i;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			err("Cannot get line");
		i++;
	}
	return (free(line), i);
}

void	check_map(char *map_file, t_mlx_data *data)
{
	check_extension(map_file);
	load_map(map_file, data);
}

void	load_map(char *map_file, t_mlx_data *data)
{
	int	fd;
	int	nb_line;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		err("Cannot open map file");
	nb_line = count_map_line(fd);
	printf("NB LINE = %d\n", nb_line);
}
