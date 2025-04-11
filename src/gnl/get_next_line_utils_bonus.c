/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:12:39 by lorey             #+#    #+#             */
/*   Updated: 2025/04/11 15:53:45 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line_bonus.h"

int	ft_strchr_gnl(const char *s, int c)
{
	int	i;

	if (!s)
		return (-1);
	i = -1;
	while (s[++i])
		if (s[i] == (char)c)
			return (i);
	if ((char)c == '\0')
		return (ft_strlen(s));
	return (-1);
}
