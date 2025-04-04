/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:46:36 by lorey             #+#    #+#             */
/*   Updated: 2025/04/04 14:20:03 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_mlx_data	data;

	setup_grid(&data);
	init(&data);
	init_img(&data);
	mlx_loop_hook(data.mlx_ptr, display, &data);
	mlx_hook(data.win_ptr, 17, 0, close_cross, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, handle_key, &data);
	mlx_key_hook(data.win_ptr, close_ESC, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
