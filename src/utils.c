/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:59:34 by lorey             #+#    #+#             */
/*   Updated: 2025/04/11 17:31:16 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	err(char *str)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (errno)
		perror(str);
	else
		ft_putstr_fd(str, STDERR_FILENO);
	exit(1);
}

void	safe_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

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
