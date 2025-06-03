/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:59:34 by lorey             #+#    #+#             */
/*   Updated: 2025/06/03 02:57:06 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	err(char *str, t_mlx_data *data)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (errno)
		perror(str);
	else
		ft_putstr_fd(str, STDERR_FILENO);
	if (data)
		free_everything(data);
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

bool	ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (false);
	}
	return (true);
}

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (true);
	return (false);
}
