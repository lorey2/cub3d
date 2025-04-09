/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:46:36 by lorey             #+#    #+#             */
/*   Updated: 2025/04/09 14:04:54 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_mlx_data	data;

	check_map_file(av[1]);
	setup_grid(&data);
	init(&data);
	init_img(&data);
	mlx_loop_hook(data.mlx_ptr, display, &data);
	mlx_hook(data.win_ptr, 17, 0, close_cross, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, key_pressed, &data);
	mlx_key_hook(data.win_ptr, close_esc, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
