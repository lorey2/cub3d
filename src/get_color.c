/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:23:11 by lorey             #+#    #+#             */
/*   Updated: 2025/04/21 18:33:22 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	setup_p_s_g(double *p_s_g, t_data *img, double offset, double player_pos)
{
	if (!img || !img->addr)
		return (-1);
	if (TILE_SIZE <= 0 || img->width <= 0
		|| img->height <= 0 || img->bits_per_pixel <= 0)
		return (-1);
	*p_s_g = offset - (TILE_SIZE - fmod(player_pos, TILE_SIZE));
	*p_s_g = fmod(*p_s_g, TILE_SIZE);
	if (*p_s_g < 0)
		*p_s_g += TILE_SIZE;
	*p_s_g *= ((double)img->width / TILE_SIZE);
	return (0);
}

int	get_color(double player_pos, t_mlx_data *data, double offset, t_data *img)
{
	int		y;
	int		pixel_index;
	int		color;
	double	p_s_g;

	if (setup_p_s_g(&p_s_g, img, offset, player_pos))
		return (0);
	y = 200;
	if ((int)p_s_g < 0)
		p_s_g = 0;
	else if ((int)p_s_g >= img->width)
		p_s_g = img->width - 1;
	if (y < 0)
		y = 0;
	else if (y >= img->height)
		y = img->height - 1;
	data->textu_x = (int)p_s_g;
	pixel_index = y * img->line_length + (int)p_s_g * (img->bits_per_pixel / 8);
	color = *(int *)(img->addr + pixel_index);
	(void)data;
	return (color);
}
