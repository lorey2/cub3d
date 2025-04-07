/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_movement_angle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:57:24 by lorey             #+#    #+#             */
/*   Updated: 2025/04/07 16:05:48 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	change_angle(t_mlx_data *data)
{
	if (data->key->q == true)
	{
		data->angle -= (M_PI / 180);
		if (data->angle < 0)
			data->angle += 2 * M_PI;
	}
	if (data->key->e == true)
	{
		data->angle += (M_PI / 180);
		if (data->angle >= 2 * M_PI)
			data->angle -= 2 * M_PI;
	}
	data->angle_bkp = data->angle;
	return (0);
}

void	set_next_pos(double next_x, double next_y, t_mlx_data *data)
{
	if (data->grid[(int)(next_x / TILE_SIZE)][(int)(next_y / TILE_SIZE)] != '1')
	{
		data->player_x = next_x;
		data->player_y = next_y;
	}
}

int	key_pressed(int keysym, t_mlx_data *data)
{
	if (keysym == XK_w)
		data->key->w = true;
	if (keysym == XK_a)
		data->key->a = true;
	if (keysym == XK_s)
		data->key->s = true;
	if (keysym == XK_d)
		data->key->d = true;
	if (keysym == XK_q)
		data->key->q = true;
	if (keysym == XK_e)
		data->key->e = true;
	return (0);
}

void	handle_key_2(t_mlx_data *data)
{
	double	next_x;
	double	next_y;

	if (data->key->d == true)
	{
		next_x = data->player_x + MV_SPD * cos(data->angle_bkp + M_PI_2);
		next_y = data->player_y + MV_SPD * sin(data->angle_bkp + M_PI_2);
		set_next_pos(next_x, next_y, data);
	}
	if (data->key->a == true)
	{
		next_x = data->player_x + MV_SPD * cos(data->angle_bkp - M_PI_2);
		next_y = data->player_y + MV_SPD * sin(data->angle_bkp - M_PI_2);
		set_next_pos(next_x, next_y, data);
	}
}

void	handle_key(t_mlx_data *data)
{
	double	next_x;
	double	next_y;

	if (data->key->w == true)
	{
		next_x = data->player_x + MV_SPD * cos(data->angle_bkp);
		next_y = data->player_y + MV_SPD * sin(data->angle_bkp);
		set_next_pos(next_x, next_y, data);
	}
	if (data->key->s == true)
	{
		next_x = data->player_x - MV_SPD * cos(data->angle_bkp);
		next_y = data->player_y - MV_SPD * sin(data->angle_bkp);
		set_next_pos(next_x, next_y, data);
	}
	handle_key_2(data);
}
