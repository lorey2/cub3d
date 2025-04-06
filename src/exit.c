/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:46:50 by lorey             #+#    #+#             */
/*   Updated: 2025/04/06 23:05:20 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_cross(t_mlx_data *data)
{
	data->player_x = 0;
	exit (0);
	return (0);
}

int	close_esc(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
	{
		data->player_x = 0;
		exit (0);
		return (0);
	}
	if (keysym == XK_w)
		data->key->w = false;
	if (keysym == XK_a)
		data->key->a = false;
	if (keysym == XK_s)
		data->key->s = false;
	if (keysym == XK_d)
		data->key->d = false;
	if (keysym == XK_q)
		data->key->q = false;
	if (keysym == XK_e)
		data->key->e = false;
	return (0);
}
