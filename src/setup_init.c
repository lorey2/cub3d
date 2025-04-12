/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:45:15 by lorey             #+#    #+#             */
/*   Updated: 2025/04/12 16:25:23 by lorey            ###   LAUSANNE.ch       */
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
	data->l = malloc(sizeof(t_dline));
	data->last_frame_time.tv_sec = 0;
	data->last_frame_time.tv_usec = 0;
	data->mlx_ptr = mlx_init();
	data->size_x_window = 500;
	data->size_y_window = 500;
	data->win_ptr = mlx_new_window
		(data->mlx_ptr, 1500, 1000, "SO_LONG");
}

void	init_a_texture(t_mlx_data *data, t_data **img, char *path)
{
	(*img)->img = mlx_xpm_file_to_image(data->mlx_ptr, path,
			&(*img)->width, &(*img)->height);
	(*img)->addr = mlx_get_data_addr((*img)->img,
			&(*img)->bits_per_pixel, &(*img)->line_length,
			&(*img)->endian);
}

void	init_minecraft_texture(t_img_ptr *img, t_mlx_data *data)
{
	img->dirt = malloc(sizeof(t_data));
	img->dirt->height = 512;
	img->dirt->width = 512;
	init_a_texture(data, &img->dirt, "./img/dirt.xpm");
	img->cobble = malloc(sizeof(t_data));
	img->cobble->height = 512;
	img->cobble->width = 512;
	init_a_texture(data, &img->cobble, "./img/cobble.xpm");
	img->diam = malloc(sizeof(t_data));
	img->diam->height = 1920;
	img->diam->width = 1920;
	init_a_texture(data, &img->diam, "./img/diam.xpm");
	img->wood = malloc(sizeof(t_data));
	img->wood->width = 1280;
	img->wood->height = 1280;
	init_a_texture(data, &img->wood, "./img/wood.xpm");
}

void	init_sky_texture(t_img_ptr *img, t_mlx_data *data)
{
	img->skyframe1 = malloc(sizeof(t_data));
	img->skyframe1->width = 64;
	img->skyframe1->height = 64;
	init_a_texture(data, &img->skyframe1, "./img/skyframe1.xpm");
	img->skyframe2 = malloc(sizeof(t_data));
	img->skyframe2->width = 64;
	img->skyframe2->height = 64;
	init_a_texture(data, &img->skyframe2, "./img/skyframe2.xpm");
	img->skyframe3 = malloc(sizeof(t_data));
	img->skyframe3->width = 64;
	img->skyframe3->height = 64;
	init_a_texture(data, &img->skyframe3, "./img/skyframe3.xpm");
	img->skyframe4 = malloc(sizeof(t_data));
	img->skyframe4->width = 64;
	img->skyframe4->height = 64;
	init_a_texture(data, &img->skyframe4, "./img/skyframe4.xpm");
	img->skyframe5 = malloc(sizeof(t_data));
	img->skyframe5->width = 64;
	img->skyframe5->height = 64;
	init_a_texture(data, &img->skyframe5, "./img/skyframe5.xpm");
	img->skyframe6 = malloc(sizeof(t_data));
	img->skyframe6->width = 64;
	img->skyframe6->height = 64;
	init_a_texture(data, &img->skyframe6, "./img/skyframe6.xpm");
	img->skyframe7 = malloc(sizeof(t_data));
	img->skyframe7->width = 64;
	img->skyframe7->height = 64;
	init_a_texture(data, &img->skyframe7, "./img/skyframe7.xpm");
	img->skyframe8 = malloc(sizeof(t_data));
	img->skyframe8->width = 64;
	img->skyframe8->height = 64;
	init_a_texture(data, &img->skyframe8, "./img/skyframe8.xpm");
}
void	init_texture(t_img_ptr *img, t_mlx_data *data)
{
	init_minecraft_texture(img, data);
	init_sky_texture(img, data);
	img->frame1 = malloc(sizeof(t_data));
	img->frame1->width = 64;
	img->frame1->height = 64;
	init_a_texture(data, &img->frame1, "./img/frame1.xpm");
	img->frame2 = malloc(sizeof(t_data));
	img->frame2->width = 64;
	img->frame2->height = 64;
	init_a_texture(data, &img->frame2, "./img/frame2.xpm");
	img->frame3 = malloc(sizeof(t_data));
	img->frame3->width = 64;
	img->frame3->height = 64;
	init_a_texture(data, &img->frame3, "./img/frame3.xpm");
	img->frame4 = malloc(sizeof(t_data));
	img->frame4->width = 64;
	img->frame4->height = 64;
	init_a_texture(data, &img->frame4, "./img/frame4.xpm");
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
