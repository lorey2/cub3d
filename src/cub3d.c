/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:46:36 by lorey             #+#    #+#             */
/*   Updated: 2025/04/23 16:22:00 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_mlx_data	data;

	if (ac != 2)
		err("You should provide only one argument", NULL);
	parsing(av[1], &data);
	free_everything(&data);
	// setup_grid(&data);
	// init(&data);
	// init_img(&data, data.img_ptr);
	// mlx_mouse_move(data.mlx_ptr, data.win_ptr, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
	// mlx_mouse_hide(data.mlx_ptr, data.win_ptr);
	// mlx_loop_hook(data.mlx_ptr, display, &data);
	// mlx_hook(data.win_ptr, 6, (1L << 6), mouse_move, &data);
	// mlx_hook(data.win_ptr, 17, 0, close_cross, &data);
	// mlx_hook(data.win_ptr, 2, 1L << 0, key_pressed, &data);
	// mlx_key_hook(data.win_ptr, close_esc, &data);
	// mlx_loop(data.mlx_ptr);
	return (0);
}
