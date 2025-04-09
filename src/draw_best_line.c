/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_best_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:48:06 by lorey             #+#    #+#             */
/*   Updated: 2025/04/09 16:48:36 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	draw_vertical_line(t_mlx_data *data, t_linex *ver)
{
	data->l->x1 = data->player_x;
	data->l->y1 = data->player_y;
	data->l->x2 = ver->delta_x;
	data->l->y2 = (int)(data->player_y + ver->offset);
	if ((data->angle > M_PI_2 && data->angle < 3 * M_PI_2)
		|| (data->angle < -1 * M_PI_2 && data->angle > -3 * M_PI_2))
	{
		data->color = GREEN;
		data->l->color = GREEN;
	}
	else
	{
		data->color = GRAY;
		data->l->color = GRAY;
	}
	draw_line(data, data->l);
	data->best = data->ray_ver;
}

void	draw_horizontal_line(t_mlx_data *data, t_liney *hor)
{
	data->l->x1 = data->player_x;
	data->l->y1 = data->player_y;
	data->l->x2 = (int)(data->player_x + hor->offset);
	data->l->y2 = hor->delta_y;
	if ((data->angle > 0 && data->angle < M_PI)
		|| (data->angle < -1 * M_PI && data->angle > -2 * M_PI))
	{
		data->l->color = WHITE;
		data->color = WHITE;
	}
	else
	{
		data->l->color = BLACK;
		data->color = BLACK;
	}
	draw_line(data, data->l);
	data->best = data->ray_hor;
}

void	draw_best_line(t_mlx_data *data)
{
	t_linex	ver;
	t_liney	hor;
	int		ver_no;
	int		hor_no;

	ver_no = ver_best_line(data, &ver);
	hor_no = hor_best_line(data, &hor);
	data->ray_hor = sqrt(pow(hor.offset, 2)
			+ pow(hor.delta_y - (double)data->player_y, 2));
	data->ray_ver = sqrt(pow(ver.delta_x - data->player_x, 2)
			+ pow(ver.offset, 2));
	if (ver_no == -1)
		draw_horizontal_line(data, &hor);
	else if (hor_no == -1)
		draw_vertical_line(data, &ver);
	else if (data->ray_ver > data->ray_hor)
		draw_horizontal_line(data, &hor);
	else
		draw_vertical_line(data, &ver);
}
