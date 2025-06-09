/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:46:36 by lorey             #+#    #+#             */
/*   Updated: 2025/06/09 15:50:31 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//if (ac != 2)
//	err("You should provide only one argument");
// check_map(av[1], &data);

int	main(int ac, char **av)
{
	t_mlx_data	data;

	if (ac != 2)
		err("You should provide only one argument", NULL);
	set_all_data_pointer_to_null(&data);
	parsing(av[1], &data);
	size_array(&data);
	init(&data);
	data.img_ptr = malloc(sizeof(t_img_ptr));
	if (!data.img_ptr)
		err("Malloc error", &data);
	init_img(&data, data.img_ptr);
	setup_rgb(&data);
	setup_player_pos_angle(&data);
	mlx_mouse_move(data.mlx_ptr, data.win_ptr, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
	mlx_mouse_hide(data.mlx_ptr, data.win_ptr);
	mlx_loop_hook(data.mlx_ptr, display, &data);
	mlx_hook(data.win_ptr, 6, (1L << 6), mouse_move, &data);
	mlx_hook(data.win_ptr, 17, 0, close_cross, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, key_pressed, &data);
	mlx_key_hook(data.win_ptr, key_released, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

void	pars_texture_helper_utils(char **split, char **map, t_mlx_data *data)
{
	if (ft_isequal(split[0], "NO") || ft_isequal(split[0], "SO")
		|| ft_isequal(split[0], "EA") || ft_isequal(split[0], "WE")
		|| ft_isequal(split[0], "F") || ft_isequal(split[0], "C")
		|| ft_isequal(split[0], "D"))
	{
		multi_free(&split);
		multi_free(&map);
		err("Duplicate texture", data);
	}
}

int	count_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}
