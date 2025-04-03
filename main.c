/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lo>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 23:16:39 by lorey             #+#    #+#             */
/*   Updated: 2025/04/03 02:07:33 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "mlx_linux/mlx.h"
#include <stdlib.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	display(t_mlx_data *data)
{
	int		x;
	int		y;
	t_data	*img;

	img = data->img_ptr;
	x = -1;
	y = -1;
	while (++x < 1920)
	{
		y = -1;
		while (++y < 1080)
			my_mlx_pixel_put(&(*img), x, y, 0x000000FF);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img->img, 0, 0);
	return (0);
}

void	init(t_mlx_data *data)
{
	data->img_ptr = malloc(sizeof(t_data));
	data->mlx_ptr = mlx_init();
	data->size_x_window = 1920;
	data->size_y_window = 1080;
	data->win_ptr = mlx_new_window
		(data->mlx_ptr, data->size_x_window, data->size_y_window, "SO_LONG");
}

void	init_img(t_mlx_data *data)
{
	data->img_ptr->img = mlx_new_image(data->mlx_ptr, 1920, 1080);
	data->img_ptr->addr = mlx_get_data_addr(data->img_ptr->img,
			&data->img_ptr->bits_per_pixel, &data->img_ptr->line_length,
			&data->img_ptr->endian);
}

int	main(void)
{
	t_mlx_data	data;

	init(&data);
	init_img(&data);
	mlx_loop_hook(data.mlx_ptr, display, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
