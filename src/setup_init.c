/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:45:15 by lorey             #+#    #+#             */
/*   Updated: 2025/04/11 19:52:49 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_mlx_data *data)
{
	data->frame_nbr = 0;
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
	data->img_ptr = malloc(sizeof(t_img_ptr));
	data->img_ptr->raycast = malloc(sizeof(t_data));
	data->img_ptr->img_ptr = malloc(sizeof(t_data));
	data->img_ptr->dirt = malloc(sizeof(t_data));
	data->img_ptr->cobble = malloc(sizeof(t_data));
	data->img_ptr->diam = malloc(sizeof(t_data));
	data->img_ptr->wood = malloc(sizeof(t_data));
	data->img_ptr->frame1 = malloc(sizeof(t_data));
	data->img_ptr->frame2 = malloc(sizeof(t_data));
	data->img_ptr->frame3 = malloc(sizeof(t_data));
	data->img_ptr->frame4 = malloc(sizeof(t_data));
	data->l = malloc(sizeof(t_dline));
	data->last_frame_time.tv_sec = 0;
	data->last_frame_time.tv_usec = 0;
	data->mlx_ptr = mlx_init();
	data->size_x_window = 500;
	data->size_y_window = 500;
	data->win_ptr = mlx_new_window
		(data->mlx_ptr, 1500, 1000, "SO_LONG");
}

void	init_texture(t_img_ptr *img, t_mlx_data *data)
{
	img->dirt->height = 512;
	img->dirt->width = 512;
	img->cobble->height = 512;
	img->cobble->width = 512;
	img->diam->height = 1920;
	img->diam->width = 1920;
	img->wood->width = 1280;
	img->wood->height = 1280;
	img->frame1->width = 64;
	img->frame1->height = 64;
	img->frame2->width = 64;
	img->frame2->height = 64;
	img->frame3->width = 64;
	img->frame3->height = 64;
	img->frame4->width = 64;
	img->frame4->height = 64;
	img->dirt->img = mlx_xpm_file_to_image(data->mlx_ptr, "./img/dirt.xpm",
			&img->dirt->width, &img->dirt->height);
	img->dirt->addr = mlx_get_data_addr(img->dirt->img,
			&img->dirt->bits_per_pixel, &img->dirt->line_length,
			&img->dirt->endian);
	img->cobble->img = mlx_xpm_file_to_image(data->mlx_ptr, "./img/cobble.xpm",
			&img->cobble->width, &img->cobble->height);
	img->cobble->addr = mlx_get_data_addr(img->cobble->img,
			&img->cobble->bits_per_pixel, &img->cobble->line_length,
			&img->cobble->endian);
	img->diam->img = mlx_xpm_file_to_image(data->mlx_ptr, "./img/diam.xpm",
			&img->diam->width, &img->diam->height);
	img->diam->addr = mlx_get_data_addr(img->diam->img,
			&img->diam->bits_per_pixel, &img->diam->line_length,
			&img->diam->endian);
	img->wood->img = mlx_xpm_file_to_image(data->mlx_ptr, "./img/wood.xpm",
			&img->wood->width, &img->wood->height);
	img->wood->addr = mlx_get_data_addr(img->wood->img,
			&img->wood->bits_per_pixel, &img->wood->line_length,
			&img->wood->endian);
	img->frame1->img = mlx_xpm_file_to_image(data->mlx_ptr, "./img/frame1.xpm",
			&img->frame1->width, &img->frame1->height);
	img->frame1->addr = mlx_get_data_addr(img->frame1->img,
			&img->frame1->bits_per_pixel, &img->frame1->line_length,
			&img->frame1->endian);
	img->frame2->img = mlx_xpm_file_to_image(data->mlx_ptr, "./img/frame2.xpm",
			&img->frame2->width, &img->frame2->height);
	img->frame2->addr = mlx_get_data_addr(img->frame2->img,
			&img->frame2->bits_per_pixel, &img->frame2->line_length,
			&img->frame2->endian);
	img->frame3->img = mlx_xpm_file_to_image(data->mlx_ptr, "./img/frame3.xpm",
			&img->frame3->width, &img->frame3->height);
	img->frame3->addr = mlx_get_data_addr(img->frame3->img,
			&img->frame3->bits_per_pixel, &img->frame3->line_length,
			&img->frame3->endian);
	img->frame4->img = mlx_xpm_file_to_image(data->mlx_ptr, "./img/frame4.xpm",
			&img->frame4->width, &img->frame4->height);
	img->frame4->addr = mlx_get_data_addr(img->frame4->img,
			&img->frame4->bits_per_pixel, &img->frame4->line_length,
			&img->frame4->endian);
}

void	init_img(t_mlx_data *data, t_img_ptr *img)
{
	init_texture(img, data);
	img->img_ptr->img = mlx_new_image(data->mlx_ptr, SIZE_MAP_X, SIZE_MAP_Y);
	img->img_ptr->addr = mlx_get_data_addr(img->img_ptr->img,
			&img->img_ptr->bits_per_pixel, &img->img_ptr->line_length,
			&img->img_ptr->endian);
	img->raycast->img = mlx_new_image(
			data->mlx_ptr, SIZE_3D_IMG_X, SIZE_3D_IMG_Y);
	img->raycast->addr = mlx_get_data_addr(img->raycast->img,
			&img->raycast->bits_per_pixel, &img->raycast->line_length,
			&img->raycast->endian);
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
