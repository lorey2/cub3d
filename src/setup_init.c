/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:21:03 by lorey             #+#    #+#             */
/*   Updated: 2025/04/21 23:08:30 by lorey            ###   LAUSANNE.ch       */
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
	data->key->mouse_x = WIN_SIZE_X / 2;
	data->is_open = false;
	data->img_arr = malloc(sizeof(t_tex_img_array));
	data->text_arr = malloc(sizeof(t_tex_name));
	data->img_ptr = malloc(sizeof(t_img_ptr));
	data->img_ptr->game = malloc(sizeof(t_data));
	data->img_ptr->minimap = malloc(sizeof(t_data));
	data->data_3d = malloc(sizeof(t_3d_data));
	data->l = malloc(sizeof(t_dline));
	data->last_frame_time.tv_sec = 0;
	data->last_frame_time.tv_usec = 0;
	data->mlx_ptr = mlx_init();
	data->size_x_window = 500;
	data->size_y_window = 500;
	data->win_ptr = mlx_new_window
		(data->mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y, "CUB3D");
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
	text_arr->floor_tex_name = malloc(sizeof(char *) * 2);
	text_arr->floor_tex_name[0] = ft_strdup("./img/dirt.xpm");
	text_arr->floor_tex_name[1] = NULL;
	text_arr->north_tex_name = malloc(sizeof(char *) * 2);
	text_arr->north_tex_name[0] = ft_strdup("./img/diam.xpm");
	text_arr->north_tex_name[1] = NULL;
	text_arr->south_tex_name = malloc(sizeof(char *) * 2);
	text_arr->south_tex_name[0] = ft_strdup("./img/cobble.xpm");
	text_arr->south_tex_name[1] = NULL;
	text_arr->east_tex_name = malloc(sizeof(char *) * 2);
	text_arr->east_tex_name[0] = ft_strdup("./img/wood.xpm");
	text_arr->east_tex_name[1] = NULL;
	text_arr->west_tex_name = malloc(sizeof(char *) * 5);
	text_arr->west_tex_name[0] = ft_strdup("./img/frame1.xpm");
	text_arr->west_tex_name[1] = ft_strdup("./img/frame2.xpm");
	text_arr->west_tex_name[2] = ft_strdup("./img/frame3.xpm");
	text_arr->west_tex_name[3] = ft_strdup("./img/frame4.xpm");
	text_arr->west_tex_name[4] = NULL;
	text_arr->door_tex_name = malloc(sizeof(char *) * 3);
	text_arr->door_tex_name[0] = ft_strdup("./img/door.xpm");
	text_arr->door_tex_name[1] = ft_strdup("./img/opendoor.xpm");
	text_arr->door_tex_name[2] = NULL;
}

void	set_img(char **path, t_data ***img, t_mlx_data *data, int tex_size)
{
	int	nbr_frame;
	int	i;

	i = -1;
	nbr_frame = -1;
	while (path[++nbr_frame])
		;
	*img = malloc(sizeof(t_data *) * (nbr_frame + 1));
	i = -1;
	while (++i < nbr_frame)
	{
		(*img)[i] = malloc(sizeof(t_data));
		(*img)[i]->width = tex_size;
		(*img)[i]->height = tex_size;
		(*img)[i]->img = mlx_xpm_file_to_image(data->mlx_ptr,
				path[i],
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

void	init_img(t_mlx_data *data, t_img_ptr *img)
{
	set_name(data->text_arr);
	set_img(data->text_arr->door_tex_name,
		&data->img_arr->door_img, data, 50);
	set_img(data->text_arr->ceiling_tex_name,
		&data->img_arr->ceiling_img, data, 64);
	set_img(data->text_arr->west_tex_name,
		&data->img_arr->west_img, data, 64);
	set_img(data->text_arr->floor_tex_name,
		&data->img_arr->floor_img, data, 1920);
	set_img(data->text_arr->east_tex_name,
		&data->img_arr->east_img, data, 1280);
	set_img(data->text_arr->north_tex_name,
		&data->img_arr->north_img, data, 1920);
	set_img(data->text_arr->south_tex_name,
		&data->img_arr->south_img, data, 512);
	img->minimap->img = mlx_new_image(data->mlx_ptr, SIZE_MAP_X, SIZE_MAP_Y);
	img->minimap->addr = mlx_get_data_addr(img->minimap->img,
			&img->minimap->bits_per_pixel, &img->minimap->line_length,
			&img->minimap->endian);
	img->game->img = mlx_new_image(
			data->mlx_ptr, SIZE_3D_IMG_X, SIZE_3D_IMG_Y);
	img->game->addr = mlx_get_data_addr(img->game->img,
			&img->game->bits_per_pixel, &img->game->line_length,
			&img->game->endian);
}

/* 	y = 12;
	data->grid = malloc(sizeof(char *) * y);
	data->grid[0] = strdup("1111111111");
	data->grid[1] = strdup("1000000001");
	data->grid[2] = strdup("1000001001");
	data->grid[3] = strdup("1000001001");
	data->grid[4] = strdup("1000001001");
	data->grid[5] = strdup("1010001001");
	data->grid[6] = strdup("100000D001");
	data->grid[7] = strdup("1000001001");
	data->grid[8] = strdup("1111111111");
	data->grid[9] = strdup("1111111111");
	data->grid[10] = strdup("1111111111");
	data->grid[11] = NULL; */

/* 	y = 21;
	data->grid = malloc(sizeof(char *) * y);
	data->grid[0] = strdup("11111111111111111111");
	data->grid[1] = strdup("10000000000001000001");
	data->grid[2] = strdup("10000000000001000001");
	data->grid[3] = strdup("10000000000001000001");
	data->grid[4] = strdup("10000000000001000001");
	data->grid[5] = strdup("10000000000001000001");
	data->grid[6] = strdup("10000000000001000001");
	data->grid[7] = strdup("10000000000001000001");
	data->grid[8] = strdup("10000000000001000001");
	data->grid[9] = strdup("10000000000001000001");
	data->grid[10] = strdup("10000000000010000001");
	data->grid[11] = strdup("10000000000010000001");
	data->grid[12] = strdup("100000000000D0000001");
	data->grid[13] = strdup("10000000000010000001");
	data->grid[14] = strdup("10000000000010000001");
	data->grid[15] = strdup("10000000000010000001");
	data->grid[16] = strdup("10000000000010000001");
	data->grid[17] = strdup("10000000000010000001");
	data->grid[18] = strdup("10000000000010000001");
	data->grid[19] = strdup("11111111111111111111");
	data->grid[20] = NULL; */

void	setup_grid(t_mlx_data *data)
{
	int	y;

	y = 15;
	data->grid = malloc(sizeof(char *) * y);
	data->grid[0] = strdup("        1111111111111111111111111");
	data->grid[1] = strdup("        100000000011000E000000001");
	data->grid[2] = strdup("        1011000001110000000000001");
	data->grid[3] = strdup("        1001000000000000000000001");
	data->grid[4] = strdup("111111111011000001110000000000001");
	data->grid[5] = strdup("100000000011000001110111111111111");
	data->grid[6] = strdup("11110111111111011100000010001    ");
	data->grid[7] = strdup("11110111111111011101010010001    ");
	data->grid[8] = strdup("11000000110101011100000010001    ");
	data->grid[9] = strdup("10000000000000001100000010001    ");
	data->grid[10] = strdup("10000000000000001101010010001    ");
	data->grid[11] = strdup("1100000111010101111101111000111  ");
	data->grid[12] = strdup("11110111 1110101 101111010001    ");
	data->grid[13] = strdup("11111111 1111111 111111111111    ");
	data->grid[14] = NULL;
}

void	setup_angle(char a, t_mlx_data *data)
{
	if (a == 'N')
		data->angle = 3 * M_PI_2;
	if (a == 'S')
		data->angle = M_PI_2;
	if (a == 'E')
		data->angle = 0;
	if (a == 'W')
		data->angle = M_PI;
}

void	setup_player_pos_angle(t_mlx_data *data)
{
	double	i;
	double	j;

	i = -1;
	j = -1;
	while (data->grid[(int)(++i)])
	{
		j = -1;
		while (data->grid[(int)i][(int)(++j)])
		{
			if (data->grid[(int)i][(int)j] == 'N'
				|| data->grid[(int)i][(int)j] == 'S'
				|| data->grid[(int)i][(int)j] == 'E'
				|| data->grid[(int)i][(int)j] == 'W')
			{
				data->player_x = (i + 0.5) * TILE_SIZE;
				data->player_y = (j + 0.5) * TILE_SIZE;
				setup_angle(data->grid[(int)i][(int)j], data);
				data->grid[(int)i][(int)j] = '0';
				return ;
			}
		}
	}
}
