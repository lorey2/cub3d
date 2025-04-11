/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_best_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:48:06 by lorey             #+#    #+#             */
/*   Updated: 2025/04/11 04:23:00 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int get_color(double player_pos, t_mlx_data *data, double offset, t_data *img)
{
    int      x;
    int      y;
    int      pixel_index;
    int      color;
    double   p_s_g;

    if (!img || !img->addr) {
        return (0);
    }
    if (TILE_SIZE <= 0 || img->width <= 0 || img->height <= 0 || img->bits_per_pixel <= 0) {
        return (0);
	}

    p_s_g = offset - (TILE_SIZE - fmod(player_pos, TILE_SIZE));
    p_s_g = fmod(p_s_g, TILE_SIZE);

    if (p_s_g < 0) {
        p_s_g += TILE_SIZE;
    }

    p_s_g *= ((double)img->width / TILE_SIZE);

    x = (int)p_s_g;
    y = 200;

    if (x < 0) {
        x = 0;
    } else if (x >= img->width) {
        x = img->width - 1;
    }

    if (y < 0) {
        y = 0;
    } else if (y >= img->height) {
        y = img->height - 1;
    }
	data->textu_x = x;
    pixel_index = y * img->line_length + x * (img->bits_per_pixel / 8);

    color = *(int *)(img->addr + pixel_index);

    (void)data;

    return (color);
}

void	draw_vertical_line(t_mlx_data *data, t_linex *ver)
{
	data->l->x1 = data->player_x;
	data->l->y1 = data->player_y;
	data->l->x2 = ver->delta_x;
	data->l->y2 = (int)(data->player_y + ver->offset);
	if ((data->angle > M_PI_2 && data->angle < 3 * M_PI_2)
		|| (data->angle < -1 * M_PI_2 && data->angle > -3 * M_PI_2))
	{
		data->color = get_color(
				data->player_y, data, ver->offset, data->diam);
		data->l->color = get_color(
				data->player_y, data, ver->offset, data->diam);
		data->selected = data->diam;
	}
	else
	{
		data->color = get_color(
				data->player_y, data, ver->offset, data->wood);
		data->l->color = get_color(
				data->player_y, data, ver->offset, data->wood);
		data->selected = data->wood;
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
		data->l->color = get_color(
				data->player_x, data, hor->offset, data->dirt);
		data->color = get_color(
				data->player_x, data, hor->offset, data->dirt);
		data->selected = data->dirt;
	}
	else
	{
		data->l->color = get_color(
				data->player_x, data, hor->offset, data->cobble);
		data->color = get_color(
				data->player_x, data, hor->offset, data->cobble);
		data->selected = data->cobble;
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
