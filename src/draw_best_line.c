/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_best_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:48:06 by lorey             #+#    #+#             */
/*   Updated: 2025/04/08 20:38:22 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	draw_vertical_line(t_mlx_data *data, t_linex *ver)
{
	draw_line(data, data->player_x, data->player_y, ver->delta_x,
		(int)(data->player_y + ver->offset), GRAY);
	data->best = data->ray_ver;
	data->color = GRAY;
}

void	draw_horizontal_line(t_mlx_data *data, t_liney *hor)
{
	draw_line(data, data->player_x, data->player_y,
		(int)(data->player_x + hor->offset), hor->delta_y, WHITE);
	data->best = data->ray_hor;
	data->color = BLACK;
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
