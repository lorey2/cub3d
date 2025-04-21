/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_best_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:54:35 by lorey             #+#    #+#             */
/*   Updated: 2025/04/21 18:23:38 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	set_ver_selected(t_mlx_data *data)
{
	if (data->is_door_ver)
	{
		if (data->is_open == false)
			data->img_ptr->selected = data->img_arr->door_img[0];
		else
			data->img_ptr->selected = data->img_arr->door_img[1];
	}
	else
	{
		if ((data->angle > M_PI_2 && data->angle < 3 * M_PI_2)
			|| (data->angle < -1 * M_PI_2 && data->angle > -3 * M_PI_2))
			data->img_ptr->selected = data->img_arr->west_img[
				(int)(((long long)data->frame_nbr
						* data->img_arr->west_img[0]->frame_nbr) / FPS)];
		else
			data->img_ptr->selected = data->img_arr->east_img[
				(int)(((long long)data->frame_nbr
						* data->img_arr->east_img[0]->frame_nbr) / FPS)];
	}
}

void	draw_vertical_line(t_mlx_data *data, t_linex *ver)
{
	data->l->x1 = data->player_x * data->mm_ratio;
	data->l->y1 = data->player_y * data->mm_ratio;
	data->l->x2 = ver->delta_x * data->mm_ratio;
	data->l->y2 = (data->player_y + ver->offset) * data->mm_ratio;
	set_ver_selected(data);
	data->l->color = get_color(
			data->player_y, data, ver->offset, data->img_ptr->selected);
	draw_line(data, data->l);
	data->best = data->ray_ver;
}

void	set_hor_selected(t_mlx_data *data)
{
	if (data->is_door_hor)
	{
		if (data->is_open == false)
			data->img_ptr->selected = data->img_arr->door_img[0];
		else
			data->img_ptr->selected = data->img_arr->door_img[1];
	}
	else
	{
		if ((data->angle > 0 && data->angle < M_PI)
			|| (data->angle < -1 * M_PI && data->angle > -2 * M_PI))
			data->img_ptr->selected = data->img_arr->north_img[
				(int)(((long long)data->frame_nbr
						* data->img_arr->north_img[0]->frame_nbr) / FPS)];
		else
			data->img_ptr->selected = data->img_arr->south_img[
				(int)(((long long)data->frame_nbr
						* data->img_arr->south_img[0]->frame_nbr) / FPS)];
	}
}

void	draw_horizontal_line(t_mlx_data *data, t_liney *hor)
{
	data->l->x1 = data->player_x * data->mm_ratio;
	data->l->y1 = data->player_y * data->mm_ratio;
	data->l->x2 = (data->player_x + hor->offset) * data->mm_ratio;
	data->l->y2 = hor->delta_y * data->mm_ratio;
	set_hor_selected(data);
	data->l->color = get_color(
			data->player_x, data, hor->offset, data->img_ptr->selected);
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
