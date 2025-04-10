/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:45:15 by lorey             #+#    #+#             */
/*   Updated: 2025/04/10 15:52:48 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_mlx_data *data)
{
	data->angle = INIT_ANGLE;
	data->player_x = PLAYER_INIT_X;
	data->player_y = PLAYER_INIT_Y;
	data->key = malloc(sizeof(t_key));
	data->key->w = false;
	data->key->a = false;
	data->key->s = false;
	data->key->d = false;
	data->key->q = false;
	data->key->e = false;
	data->raycast = malloc(sizeof(t_data));
	data->img_ptr = malloc(sizeof(t_data));
	data->l = malloc(sizeof(t_dline));
	data->last_frame_time.tv_sec = 0;
	data->last_frame_time.tv_usec = 0;
	data->mlx_ptr = mlx_init();
	data->size_x_window = 500;
	data->size_y_window = 500;
	data->win_ptr = mlx_new_window
		(data->mlx_ptr, 1500, 1000, "SO_LONG");
}

void	init_img(t_mlx_data *data)
{
	data->img_ptr->img = mlx_new_image(data->mlx_ptr, SIZE_MAP_X, SIZE_MAP_Y);
	data->img_ptr->addr = mlx_get_data_addr(data->img_ptr->img,
			&data->img_ptr->bits_per_pixel, &data->img_ptr->line_length,
			&data->img_ptr->endian);
	data->raycast->img = mlx_new_image(
			data->mlx_ptr, SIZE_3D_IMG_X, SIZE_3D_IMG_Y);
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
