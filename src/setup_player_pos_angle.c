/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_player_pos_angle.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:21:52 by lorey             #+#    #+#             */
/*   Updated: 2025/04/25 15:43:37 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_angle(char a, t_mlx_data *data)
{
	if (a == 'N')
		data->angle = M_PI;
	if (a == 'S')
		data->angle = 0;
	if (a == 'E')
		data->angle = M_PI_2;
	if (a == 'W')
		data->angle = 3 * M_PI_2;
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
