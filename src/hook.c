/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:44:15 by lorey             #+#    #+#             */
/*   Updated: 2025/04/04 19:34:17 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int	close_cross(t_mlx_data *data)
{
	data->player_x = 0;
	exit (0);
	return (0);
}

void	change_angle(int keysym, t_mlx_data *data)
{
	if (keysym == XK_q)
	{
		data->angle -= (M_PI / 180);
		if (data->angle < -2 * M_PI)
			data->angle = 0;
	}
	if (keysym == XK_e)
	{
		data->angle += (M_PI / 180);
		if (data->angle > 2 * M_PI)
			data->angle = 0;
	}
}

int	handle_key(int keysym, t_mlx_data *data)
{
	change_angle(keysym, data);
	if (keysym == XK_w
		&& data->grid[data->player_x / TILE_SIZE]
		[(data->player_y - MV_SPD) / TILE_SIZE] != '1')
		data->player_y -= MV_SPD;
	if (keysym == XK_s
		&& data->grid[data->player_x / TILE_SIZE]
		[(data->player_y + MV_SPD) / TILE_SIZE] != '1')
		data->player_y += MV_SPD;
	if (keysym == XK_d
		&& data->grid[(data->player_x + MV_SPD) / TILE_SIZE]
		[data->player_y / TILE_SIZE] != '1')
		data->player_x += MV_SPD;
	if (keysym == XK_a
		&& data->grid[(data->player_x - MV_SPD) / TILE_SIZE]
		[data->player_y / TILE_SIZE] != '1')
		data->player_x -= MV_SPD;
	return (0);
}

void	draw_best_line(t_mlx_data *data)
{
	int		x;
	double	delta_x;
	double	offset;

	x = 0;
	while (1)
	{
		delta_x = (data->player_x + x * TILE_SIZE) - (data->player_x % TILE_SIZE);
		offset = tan(data->angle) * delta_x;
		if (data->grid[data->player_x / TILE_SIZE + (x) + 1][(int)((data->player_y + offset) / TILE_SIZE)] == '1')
			break ;
		x++;
	}
	draw_line(data, data->player_x, data->player_y, data->player_x + delta_x - (data->player_x % TILE_SIZE), data->player_y + offset, 0xFFFFFFFF);
}

int	display(t_mlx_data *data)
{
	int		x;
	int		y;
	t_data	*img;

	img = data->img_ptr;
	x = -1;
	y = -1;
	while (++x < 500)
	{
		y = -1;
		while (++y < 500)
			my_mlx_pixel_put(&(*img), x, y, 0x00FF0000);
	}
	draw_grid(img, data);
	draw_player(img, data);
	draw_best_line(data);
//	draw_line(data, data->player_x, data->player_y, data->player_x + (int)(cos(data->angle) * 20), data->player_y + (int)(sin(data->angle) * 20), 0xFFFFFFFF);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img->img, 0, 0);
	return (0);
}

int	close_ESC(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
	{
		data->player_x = 0;
		exit (0);
		return (0);
	}
	return (0);
}
