/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:46:36 by lorey             #+#    #+#             */
/*   Updated: 2025/05/02 16:12:12 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//if (ac != 2)
//	err("You should provide only one argument");
// check_map(av[1], &data);

int	main(int ac, char **av)
{
	// char **t = ft_split("200,200,", ',');
	// multi_free(&t);
	// return (0);
	t_mlx_data	data;

	if (ac != 2)
		err("You should provide only one argument", NULL);
	set_all_data_pointer_to_null(&data);
	parsing(av[1], &data);
	free_everything(&data);
	// size_array(&data);
	// init(&data);
	// data.img_ptr = malloc(sizeof(t_img_ptr));
	// init_img(&data, data.img_ptr);
	// setup_player_pos_angle(&data);
	// mlx_mouse_move(data.mlx_ptr, data.win_ptr, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
	// mlx_mouse_hide(data.mlx_ptr, data.win_ptr);
	// mlx_loop_hook(data.mlx_ptr, display, &data);
	// mlx_hook(data.win_ptr, 6, (1L << 6), mouse_move, &data);
	// mlx_hook(data.win_ptr, 17, 0, close_cross, &data);
	// mlx_hook(data.win_ptr, 2, 1L << 0, key_pressed, &data);
	// mlx_key_hook(data.win_ptr, key_released, &data);
	// mlx_loop(data.mlx_ptr);
	// return (0);
}
