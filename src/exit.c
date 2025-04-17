/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:46:50 by lorey             #+#    #+#             */
/*   Updated: 2025/04/17 14:59:28 by maambuhl         ###   LAUSANNE.ch       */
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
		free_everything(data);
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
	if (keysym == XK_l)
	{
		if (data->is_open == true)
			data->is_open = false;
		else
			data->is_open = true;
	}
	return (0);
}
