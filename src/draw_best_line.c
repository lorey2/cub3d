/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_best_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:48:06 by lorey             #+#    #+#             */
/*   Updated: 2025/04/06 02:56:36 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int	setup_hor(t_mlx_data *data, t_liney *hor)
{
	hor->y = 0;
	hor->neg = 0;
	if ((data->angle < 0 && data->angle > -M_PI)
		|| (data->angle > M_PI && data->angle < 2 * M_PI))
		hor->neg = -1;
	if ((data->angle > 0 - TOLERANCE
			&& data->angle < 0 + TOLERANCE)
		|| (data->angle > M_PI - TOLERANCE
			&& data->angle < M_PI + TOLERANCE))
		return (-1);
	if ((data->angle < -M_PI + TOLERANCE
			&& data->angle > -M_PI - TOLERANCE)
		|| (data->angle < -2 * M_PI + TOLERANCE
			&& data->angle > -2 * M_PI - TOLERANCE)
		|| (data->angle < 2 * M_PI + TOLERANCE
			&& data->angle > 2 * M_PI - TOLERANCE))
		return (-1);
	return (0);
}


int	hor_best_line(t_mlx_data *data, t_liney *hor)
{
	if (setup_hor(data, hor) != -0)
		return (-1);
	while (hor->y < MAX_RAY_STEPS)
	{
		if (hor->neg == 0)
			hor->delta_y = floor((double)data->player_y / TILE_SIZE + 1 + hor->y) * TILE_SIZE;
		else
			hor->delta_y = floor((double)data->player_y / TILE_SIZE - hor->y) * TILE_SIZE;
		hor->offset = (hor->delta_y - data->player_y) / tan(data->angle) ;
		if (data->player_x + hor->offset > data->size_x_window
			|| data->player_x + hor->offset < 0)
			break ;
		hor->row_index = (int)(hor->delta_y / TILE_SIZE);
		hor->col_index = (int)(floor((data->player_x + hor->offset) / TILE_SIZE));
		if (data->grid[hor->col_index][hor->row_index + hor->neg] == '1')
			break ;
		hor->y++;
	}
	return (0);
}

int	setup_ver(t_mlx_data *data, t_linex *ver)
{
	ver->x = 0;
	ver->neg = 0;
	if ((data->angle < -M_PI / 2 && data->angle > -3 * M_PI / 2)
		|| (data->angle > M_PI / 2 && data->angle < 3 * M_PI / 2))
		ver->neg = -1;
	if ((data->angle > M_PI / 2 - TOLERANCE
			&& data->angle < M_PI / 2 + TOLERANCE)
		|| (data->angle > 3 * M_PI / 2 - TOLERANCE
			&& data->angle < 3 * M_PI / 2 + TOLERANCE))
		return (-1);
	if ((data->angle < -M_PI / 2 + TOLERANCE
			&& data->angle > -M_PI / 2 - TOLERANCE)
		|| (data->angle < -3 * M_PI / 2 + TOLERANCE
			&& data->angle > -3 * M_PI / 2 - TOLERANCE))
		return (-1);
	return (0);
}

int	ver_best_line(t_mlx_data *data, t_linex *ver)
{
	if (setup_ver(data, ver) != -0)
		return (-1);
	while (ver->x < MAX_RAY_STEPS)
	{
		if (ver->neg == 0)
			ver->delta_x = floor((double)data->player_x / TILE_SIZE + 1 + ver->x) * TILE_SIZE;
		else
			ver->delta_x = floor((double)data->player_x / TILE_SIZE - ver->x) * TILE_SIZE;
		ver->offset = tan(data->angle) * (ver->delta_x - data->player_x);
		if (data->player_y + ver->offset > data->size_y_window
			|| data->player_y + ver->offset < 0)
			break ;
		ver->col_index = (int)(ver->delta_x / TILE_SIZE);
		ver->row_index = (int)(floor((data->player_y + ver->offset) / TILE_SIZE));
		if (data->grid[ver->col_index + ver->neg][ver->row_index] == '1')
			break ;
		ver->x++;
	}
	return (0);
}

void	draw_vertical_line(t_mlx_data *data, t_linex *ver)
{

	draw_line(data, data->player_x, data->player_y, ver->delta_x, (int)(data->player_y + ver->offset), GRAY);
	data->best = data->ray_ver;
	data->color = GRAY;
}

void	draw_horizontal_line(t_mlx_data *data, t_liney *hor)
{
	draw_line(data, data->player_x, data->player_y, (int)(data->player_x + hor->offset), hor->delta_y, WHITE);
	data->best = data->ray_hor;
	data->color = BLACK;
}

void	draw_best_line(t_mlx_data *data)
{
	//printf("%f\n", data->angle);
	t_linex	ver;
	t_liney	hor;
	int		ver_no;
	int		hor_no;

	ver_no = ver_best_line(data, &ver);
	hor_no = hor_best_line(data, &hor);
	data->ray_hor = sqrt(pow(hor.offset, 2) + pow(hor.delta_y - (double)data->player_y, 2));
	data->ray_ver = sqrt(pow(ver.delta_x -data->player_x, 2) + pow(ver.offset, 2));
	if (ver_no == -1)
		draw_horizontal_line(data, &hor);
		//draw_line(data, data->player_x, data->player_y, (int)(data->player_x + hor.offset), hor.delta_y, WHITE);
	else if (hor_no == -1)
		draw_vertical_line(data, &ver);
		//draw_line(data, data->player_x, data->player_y, ver.delta_x, (int)(data->player_y + ver.offset), GRAY);
	else if (data->ray_ver > data->ray_hor)
		draw_horizontal_line(data, &hor);
		//draw_line(data, data->player_x, data->player_y, (int)(data->player_x + hor.offset), hor.delta_y, WHITE);
	else
		draw_vertical_line(data, &ver);
		//draw_line(data, data->player_x, data->player_y, ver.delta_x, (int)(data->player_y + ver.offset), GRAY);
}
