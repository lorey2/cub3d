/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:57:04 by lorey             #+#    #+#             */
/*   Updated: 2025/06/02 23:03:37 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_data *img, int x, int y, t_mlx_data *data)
{
	int	current_pixel_x;
	int	current_pixel_y;
	int	end_pixel_x;
	int	end_pixel_y;

	current_pixel_x = round(x * TILE_SIZE * data->mm_ratio);
	current_pixel_y = round(y * TILE_SIZE * data->mm_ratio);
	end_pixel_x = round((x * TILE_SIZE + TILE_SIZE) * data->mm_ratio);
	end_pixel_y = round((y * TILE_SIZE + TILE_SIZE) * data->mm_ratio);
	while (current_pixel_x < end_pixel_x)
	{
		current_pixel_y = round(y * TILE_SIZE * data->mm_ratio);
		while (current_pixel_y < end_pixel_y)
		{
			my_mlx_pixel_put(&(*img), current_pixel_x,
				current_pixel_y, data->color);
			current_pixel_y++;
		}
		current_pixel_x++;
	}
}

void	setup_line(t_dline *l)
{
	l->dx = abs(l->x2 - l->x1);
	l->dy = abs(l->y2 - l->y1);
	if (l->x1 < l->x2)
		l->sx = 1;
	else
		l->sx = -1;
	if (l->y1 < l->y2)
		l->sy = 1;
	else
		l->sy = -1;
	l->err = l->dx - l->dy;
}

void	draw_line(t_mlx_data *data, t_dline *l)
{
	setup_line(l);
	while (1)
	{
		if (l->x1 >= 0 && l->x1 < data->size_x_window
			&& l->y1 >= 0 && l->y1 < data->size_y_window)
			my_mlx_pixel_put(&(*data->img_ptr->minimap),
				l->y1, l->x1, l->color);
		if (l->x1 == l->x2 && l->y1 == l->y2)
			break ;
		l->e2 = 2 * l->err;
		if (l->e2 >= -1 * l->dy)
		{
			l->err = l->err - l->dy;
			l->x1 = l->x1 + l->sx;
		}
		if (l->e2 <= l->dx)
		{
			l->err = l->err + l->dx;
			l->y1 = l->y1 + l->sy;
		}
	}
}

void	setup_y_size(t_mlx_data *data)
{
	int	i;

	i = -1;
	while (data->grid[++i])
		;
	data->y_size = i * TILE_SIZE * data->mm_ratio;
}

void	size_array(t_mlx_data *data)
{
	int	i;
	int	j;
	int	tmp;

	i = -1;
	j = 0;
	tmp = 0;
	while (data->grid[++i])
	{
		tmp = ft_strlen(data->grid[i]);
		if (tmp > j)
			j = tmp;
	}
	data->tile_x_nbr = i;
	data->tile_y_nbr = j;
	if (i > j)
		data->tile_max_nbr = i;
	else
		data->tile_max_nbr = j;
	if (i >= 10 || j >= 10)
		data->mm_ratio = 500 / (data->tile_max_nbr * TILE_SIZE);
	else
		data->mm_ratio = 1;
	setup_y_size(data);
}
