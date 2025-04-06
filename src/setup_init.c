/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:45:15 by lorey             #+#    #+#             */
/*   Updated: 2025/04/06 02:22:33 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	init(t_mlx_data *data)
{
	data->angle = M_PI / 2;
	data->player_x = 60;
	data->player_y = 320;
	data->raycast = malloc(sizeof(t_data));
	data->img_ptr = malloc(sizeof(t_data));
	data->mlx_ptr = mlx_init();
	data->size_x_window = 500;
	data->size_y_window = 500;
	data->win_ptr = mlx_new_window
		(data->mlx_ptr, 1500, 1000, "SO_LONG");
}

void	init_img(t_mlx_data *data)
{
	data->img_ptr->img = mlx_new_image(data->mlx_ptr, 500, 500);
	data->img_ptr->addr = mlx_get_data_addr(data->img_ptr->img,
			&data->img_ptr->bits_per_pixel, &data->img_ptr->line_length,
			&data->img_ptr->endian);
	data->raycast->img = mlx_new_image(data->mlx_ptr, S_RAY_X, S_RAY_Y);
	data->raycast->addr = mlx_get_data_addr(data->raycast->img,
			&data->raycast->bits_per_pixel, &data->raycast->line_length,
			&data->raycast->endian);
}

void	setup_grid(t_mlx_data *data)
{
	int	y;

	y = 11;
	data->grid = malloc(sizeof(char *) * y);
	data->grid[0] = strdup("1111111111");
	data->grid[1] = strdup("1000000001");
	data->grid[2] = strdup("1000001001");
	data->grid[3] = strdup("1000001001");
	data->grid[4] = strdup("1000001001");
	data->grid[5] = strdup("1010001001");
	data->grid[6] = strdup("1000001001");
	data->grid[7] = strdup("1000001001");
	data->grid[8] = strdup("1000001001");
	data->grid[9] = strdup("1111111111");
	data->grid[10] = NULL;
}
