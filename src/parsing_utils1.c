/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <maambuhl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:46:06 by maambuhl          #+#    #+#             */
/*   Updated: 2025/04/24 15:58:38 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_line_sanity(char *line)
{
	if (ft_strisspace(line) || !*line)
		return (false);
	return (true);
}

int	open_helper(char *map_file, t_mlx_data *data)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		err("Cannot open map file\n", data);
	return (fd);
}

void	remove_last_map_line(t_mlx_data *data)
{
	int	i;

	i = 0;
	while (data->grid[i++])
		;
	i -= 2;
	while (i)
	{
		if (!check_line_sanity(data->grid[i]))
			safe_free((void **)&data->grid[i]);
		i--;
	}
}

size_t	get_longest_line(t_mlx_data *data)
{
	size_t	longest_line;
	size_t	len;
	int	i;

	longest_line = 0;
	i = 0;
	while (data->grid[i])
	{
		len = ft_strlen(data->grid[i++]);
		if (len > longest_line)
			longest_line = len;
	}
	return (longest_line);
}

int	count_map_line(t_mlx_data *data)
{
	int	i;

	i = 0;
	while (data->grid[i])
		i++;
	return (i);
}
