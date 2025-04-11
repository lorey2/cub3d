/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maambuhl <marcambuehl4@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:24:11 by maambuhl          #+#    #+#             */
/*   Updated: 2025/04/11 18:24:26 by maambuhl         ###   LAUSANNE.ch       */
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
