/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_movement_angle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:57:24 by lorey             #+#    #+#             */
/*   Updated: 2025/04/11 17:55:24 by lorey            ###   LAUSANNE.ch       */
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

bool	check_next(t_mlx_data *data, double x, double y)
{
	if (data->grid[(int)((x + SAFETY) / TILE_SIZE)]
		[(int)(y / TILE_SIZE)] == '1')
		return (false);
	else if (data->grid[(int)((x - SAFETY) / TILE_SIZE)]
			[(int)(y / TILE_SIZE)] == '1')
		return (false);
	else if (data->grid[(int)(x / TILE_SIZE)]
			[(int)((y + SAFETY) / TILE_SIZE)] == '1')
		return (false);
	else if (data->grid[(int)(x / TILE_SIZE)]
			[(int)((y - SAFETY) / TILE_SIZE)] == '1')
		return (false);
	return (true);
}

void	handle_key_2(t_mlx_data *data)
{
	if (data->key->d == true)
	{
		data->next_s_x = data->player_x
			+ MV_SPD * cos(data->angle_bkp + M_PI_2);
		data->next_s_y = data->player_y
			+ MV_SPD * sin(data->angle_bkp + M_PI_2);
		if (check_next(data, data->next_s_x, data->next_s_y))
		{
			data->player_x = data->next_s_x;
			data->player_y = data->next_s_y;
		}
	}
	if (data->key->a == true)
	{
		data->next_s_x = data->player_x
			+ MV_SPD * cos(data->angle_bkp - M_PI_2);
		data->next_s_y = data->player_y
			+ MV_SPD * sin(data->angle_bkp - M_PI_2);
		if (check_next(data, data->next_s_x, data->next_s_y))
		{
			data->player_x = data->next_s_x;
			data->player_y = data->next_s_y;
		}
	}
}

void	handle_key(t_mlx_data *data)
{
	if (data->key->w == true)
	{
		data->next_s_x = data->player_x
			+ MV_SPD * cos(data->angle_bkp);
		data->next_s_y = data->player_y
			+ MV_SPD * sin(data->angle_bkp);
		if (check_next(data, data->next_s_x, data->next_s_y))
		{
			data->player_x = data->next_s_x;
			data->player_y = data->next_s_y;
		}
	}
	if (data->key->s == true)
	{
		data->next_s_x = data->player_x - MV_SPD
			* cos(data->angle_bkp);
		data->next_s_y = data->player_y - MV_SPD
			* sin(data->angle_bkp);
		if (check_next(data, data->next_s_x, data->next_s_y))
		{
			data->player_x = data->next_s_x;
			data->player_y = data->next_s_y;
		}
	}
	handle_key_2(data);
}
