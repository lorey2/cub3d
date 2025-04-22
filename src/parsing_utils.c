/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <maambuhl@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:48:07 by maambuhl          #+#    #+#             */
/*   Updated: 2025/04/22 17:01:16 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (true);
	return (false);
}

bool	ft_strisspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\v')
			i++;
	}
	if (str[i] == '\0')
		return (true);
	return (false);
}

// char	*get_texture_value(char *line, t_mlx_data *data)
// {
// 	int		i;
// 	int		j;
// 	char	*value;
//
// 	i = 0;
// 	while (ft_isspace(line[i]))
// 		i++;
// 	j = 0;
// 	while (line[i + j] != '\n')
// 		j++;
// 	value = malloc(sizeof(char) * (j + 1));
// 	if (!value)
// 		err("Cannot allocate memory for texture value\n", data);
// 	j = 0;
// 	while (line[i + j] != '\n')
// 	{
// 		value[j] = line[i + j];
// 		j++;
// 	}
// 	value[j] = '\0';
// 	return (value);
// }

void	remove_texture_from_map(char **map, int line_to_rm, t_mlx_data *data)
{
	int	i;

	i = 0;
	while (i < line_to_rm)
		safe_free((void **)&map[i++]);
	// while (map[i])
	// {
	// 	if (*map[i])
	// 		safe_free((void **)&map[i]);
	// 	else if (ft_strisspace(map[i]))
	// 		safe_free((void **)&map[i]);
	// 	i++;
	// }
	data->grid = map + i;
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

bool	check_all_texture(t_mlx_data *data)
{
	t_tex_name	*tex;

	tex = data->text_arr;
	if (!tex->ceiling_tex_name || !tex->floor_tex_name || !tex->east_tex_name
		|| !tex->north_tex_name || !tex->south_tex_name || !tex->west_tex_name)
		return (false);
	return (true);
}

int	check_texture(char **map, t_mlx_data *data)
{
	int	i;

	i = -1;
	while (map[++i])
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
		else if (check_all_texture(data))
			break ;
	}
	return (i);
}
