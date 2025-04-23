/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:37:51 by lorey             #+#    #+#             */
/*   Updated: 2025/04/21 23:07:28 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_door_wall(t_mlx_data *data, int x, int y, bool is_hor)
{
	if (data->grid[x][y] == 'D' && is_hor)
		data->is_door_hor = true;
	if (data->grid[x][y] == 'D' && !is_hor)
		data->is_door_ver = true;
	if (data->grid[x][y] == '1'
		|| data->grid[x][y] == 'D' || data->grid[x][y] == ' ')
		return (1);
	return (0);
}

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
			hor->delta_y = floor((double)data->player_y
					/ TILE_SIZE + 1 + hor->y) * TILE_SIZE;
		else
			hor->delta_y = floor((double)data->player_y
					/ TILE_SIZE - hor->y) * TILE_SIZE;
		hor->offset = (hor->delta_y - data->player_y) / tan(data->angle);
		if (data->player_x + hor->offset > data->tile_x_nbr * TILE_SIZE
			|| data->player_x + hor->offset < 0)
			break ;
		hor->row_index = (int)(hor->delta_y / TILE_SIZE);
		hor->col_index = (int)(floor((data->player_x + hor->offset)
					/ TILE_SIZE));
		if (is_door_wall(data, hor->col_index, hor->row_index + hor->neg, true))
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
			ver->delta_x = floor((double)data->player_x
					/ TILE_SIZE + 1 + ver->x) * TILE_SIZE;
		else
			ver->delta_x = floor((double)data->player_x
					/ TILE_SIZE - ver->x) * TILE_SIZE;
		ver->offset = tan(data->angle) * (ver->delta_x - data->player_x);
		if (data->player_y + ver->offset > data->tile_y_nbr * TILE_SIZE
			|| data->player_y + ver->offset < 0)
			break ;
		ver->col_index = (int)(ver->delta_x / TILE_SIZE);
		ver->row_index = (int)(floor((data->player_y + ver->offset)
					/ TILE_SIZE));
		if (is_door_wall(data, ver->col_index + ver->neg,
				ver->row_index, false))
			break ;
		ver->x++;
	}
	return (0);
}
