/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:21:03 by lorey             #+#    #+#             */
/*   Updated: 2025/04/13 20:42:24 by lorey            ###   LAUSANNE.ch       */
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
	data->img_arr = malloc(sizeof(t_tex_img_array));
	data->text_arr = malloc(sizeof(t_tex_name));
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

void	set_name(t_tex_name *text_arr)
{
	text_arr->ceiling_tex_name = malloc(sizeof(char *) * 9);
	text_arr->ceiling_tex_name[0] = ft_strdup("./img/skyframe1.xpm");
	text_arr->ceiling_tex_name[1] = ft_strdup("./img/skyframe2.xpm");
	text_arr->ceiling_tex_name[2] = ft_strdup("./img/skyframe3.xpm");
	text_arr->ceiling_tex_name[3] = ft_strdup("./img/skyframe4.xpm");
	text_arr->ceiling_tex_name[4] = ft_strdup("./img/skyframe5.xpm");
	text_arr->ceiling_tex_name[5] = ft_strdup("./img/skyframe6.xpm");
	text_arr->ceiling_tex_name[6] = ft_strdup("./img/skyframe7.xpm");
	text_arr->ceiling_tex_name[7] = ft_strdup("./img/skyframe8.xpm");
	text_arr->ceiling_tex_name[8] = NULL;
	text_arr->ceiling_tex_height = 64;
	text_arr->ceiling_tex_width = 64;
	text_arr->west_tex_name = malloc(sizeof(char *) * 5);
	text_arr->west_tex_name[0] = ft_strdup("./img/frame1");
	text_arr->west_tex_name[1] = ft_strdup("./img/frame2");
	text_arr->west_tex_name[2] = ft_strdup("./img/frame3");
	text_arr->west_tex_name[3] = ft_strdup("./img/frame4");
	text_arr->west_tex_name[3] = NULL;
	text_arr->west_tex_height = 64;
	text_arr->west_tex_width = 64;
}

void	set_img(t_tex_name *text_arr, t_data ***img, t_mlx_data *data, int tex_size)
{
	int	nbr_frame;
	int	i;

	i = -1;
	nbr_frame = -1;
	while (text_arr->ceiling_tex_name[++nbr_frame])
		;
	*img = malloc(sizeof(t_data *) * (nbr_frame + 1));
	i = -1;
	while (++i < nbr_frame)
	{
		(*img)[i] = malloc(sizeof(t_data));
		(*img)[i]->width = tex_size;
		(*img)[i]->height = tex_size;
		(*img)[i]->img = mlx_xpm_file_to_image(data->mlx_ptr,
				text_arr->ceiling_tex_name[i],
				&(*img)[i]->width,
				&(*img)[i]->height);
		(*img)[i]->addr = mlx_get_data_addr((*img)[i]->img,
				&(*img)[i]->bits_per_pixel,
				&(*img)[i]->line_length,
				&(*img)[i]->endian);
	}
	(*img)[0]->frame_nbr = nbr_frame;
	(*img)[i] = NULL;
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

void	init_texture(t_img_ptr *img, t_mlx_data *data)
{
	init_minecraft_texture(img, data);
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
	set_name(data->text_arr);
	set_img(data->text_arr, &data->img_arr->ceiling_img, data, 64);
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
