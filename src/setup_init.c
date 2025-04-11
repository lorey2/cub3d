/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:45:15 by lorey             #+#    #+#             */
/*   Updated: 2025/04/11 03:49:47 by lorey            ###   LAUSANNE.ch       */
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
	data->dirt = malloc(sizeof(t_data));
	data->cobble = malloc(sizeof(t_data));
	data->diam = malloc(sizeof(t_data));
	data->wood = malloc(sizeof(t_data));
	data->l = malloc(sizeof(t_dline));
	data->last_frame_time.tv_sec = 0;
	data->last_frame_time.tv_usec = 0;
	data->mlx_ptr = mlx_init();
	data->size_x_window = 500;
	data->size_y_window = 500;
	data->win_ptr = mlx_new_window
		(data->mlx_ptr, 1500, 1000, "SO_LONG");
}

void	init_texture(t_mlx_data *data)
{
	data->dirt->height = 512;
	data->dirt->width = 512;
	data->cobble->height = 512;
	data->cobble->width = 512;
	data->diam->height = 1920;
	data->diam->width = 1920;
	data->wood->width = 1280;
	data->wood->height = 1280;
	data->dirt->img = mlx_xpm_file_to_image(data->mlx_ptr, "./img/dirt.xpm",
			&data->dirt->width, &data->dirt->height);
	data->dirt->addr = mlx_get_data_addr(data->dirt->img,
			&data->dirt->bits_per_pixel, &data->dirt->line_length,
			&data->dirt->endian);
	data->cobble->img = mlx_xpm_file_to_image(data->mlx_ptr, "./img/cobble.xpm",
			&data->cobble->width, &data->cobble->height);
	data->cobble->addr = mlx_get_data_addr(data->cobble->img,
			&data->cobble->bits_per_pixel, &data->cobble->line_length,
			&data->cobble->endian);
	data->diam->img = mlx_xpm_file_to_image(data->mlx_ptr, "./img/diam.xpm",
			&data->diam->width, &data->diam->height);
	data->diam->addr = mlx_get_data_addr(data->diam->img,
			&data->diam->bits_per_pixel, &data->diam->line_length,
			&data->diam->endian);
	data->wood->img = mlx_xpm_file_to_image(data->mlx_ptr, "./img/wood.xpm",
			&data->wood->width, &data->wood->height);
	data->wood->addr = mlx_get_data_addr(data->wood->img,
			&data->wood->bits_per_pixel, &data->wood->line_length,
			&data->wood->endian);
}

void	init_img(t_mlx_data *data)
{
	init_texture(data);
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
