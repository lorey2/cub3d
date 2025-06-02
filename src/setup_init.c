/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:21:03 by lorey             #+#    #+#             */
/*   Updated: 2025/05/09 18:04:10 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//usefull for safefree

void	set_all_data_pointer_to_null(t_mlx_data *data)
{
	data->img_arr = NULL;
	data->text_arr = NULL;
	data->key = NULL;
	data->l = NULL;
	data->img_ptr = NULL;
	data->data_3d = NULL;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->grid = NULL;
	data->rgb_data = NULL;
}

void	setup_first_variable(t_mlx_data *data)
{
	data->frame_nbr = 0;
	data->angle = INIT_ANGLE;
	data->player_x = PLAYER_INIT_X;
	data->player_y = PLAYER_INIT_Y;
	data->is_open = false;
	data->last_frame_time.tv_sec = 0;
	data->last_frame_time.tv_usec = 0;
	data->size_x_window = 500;
	data->size_y_window = 500;
	data->key = malloc(sizeof(t_key));
	data->key->w = false;
	data->key->a = false;
	data->key->s = false;
	data->key->d = false;
	data->key->q = false;
	data->key->e = false;
	data->key->mouse_x = WIN_SIZE_X / 2;
}

void	init(t_mlx_data *data)
{
	setup_first_variable(data);
	data->data_3d = malloc(sizeof(t_3d_data));
	data->l = malloc(sizeof(t_dline));
	data->rgb_data = malloc(sizeof(t_rgb_data));
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window
		(data->mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y, "CUB3D");
}

void	init_texture(t_tex_name *tex)
{
	tex->ceiling_tex_name = NULL;
	tex->door_tex_name = NULL;
	tex->east_tex_name = NULL;
	tex->floor_tex_name = NULL;
	tex->north_tex_name = NULL;
	tex->south_tex_name = NULL;
	tex->west_tex_name = NULL;
	tex->c_size = 50;
	tex->d_size = 50;
	tex->e_size = 50;
	tex->f_size = 50;
	tex->n_size = 50;
	tex->s_size = 50;
	tex->w_size = 50;
}
