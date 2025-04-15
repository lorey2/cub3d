/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <maambuhl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:48:07 by maambuhl          #+#    #+#             */
/*   Updated: 2025/04/15 17:14:39 by maambuhl         ###   LAUSANNE.ch       */
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

void	checktext_file(t_mlx_data *data)
{
	int	i;

	i = 0;
	
}

void	check_texture(char **map, t_mlx_data *data)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == 'N' && map[i][1] == 'O' && ft_isspace(map[i][2]))
			data->text_arr->north_tex_name = ft_split(map[i] + 2, ' ');
		else if (map[i][0] == 'S' && map[i][1] == 'O' && ft_isspace(map[i][2]))
			data->text_arr->south_tex_name = ft_split(map[i] + 2, ' ');
		else if (map[i][0] == 'W' && map[i][1] == 'E' && ft_isspace(map[i][2]))
			data->text_arr->west_tex_name = ft_split(map[i] + 2, ' ');
		else if (map[i][0] == 'E' && map[i][1] == 'A' && ft_isspace(map[i][2]))
			data->text_arr->east_tex_name = ft_split(map[i] + 2, ' ');
		else if (map[i][0] == 'F' && ft_isspace(map[i][1]))
			data->text_arr->floor_tex_name = ft_split(map[i] + 1, ' ');
		else if (map[i][0] == 'C' && ft_isspace(map[i][1]))
			data->text_arr->ceiling_tex_name = ft_split(map[i] + 1, ' ');
		i++;
	}
}
