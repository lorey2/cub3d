/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lo>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 23:16:39 by lorey             #+#    #+#             */
/*   Updated: 2025/04/04 03:57:12 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "mlx_linux/mlx.h"
#include <stdlib.h>

int	close_cross(t_mlx_data *data)
{
	exit (0);
	return (0);
}

int	handle_key(int keysym, t_mlx_data *data)
{
	if (keysym == XK_w
		&& data->grid[data->player_x / TILE_SIZE]
		[(data->player_y - MV_SPD) / TILE_SIZE] != '1')
		data->player_y -= MV_SPD;
	if (keysym == XK_s
		&& data->grid[data->player_x / TILE_SIZE]
		[(data->player_y + MV_SPD) / TILE_SIZE] != '1')
		data->player_y += MV_SPD;
	if (keysym == XK_d
		&& data->grid[(data->player_x + MV_SPD) / TILE_SIZE]
		[data->player_y / TILE_SIZE] != '1')
		data->player_x += MV_SPD;
	if (keysym == XK_a
		&& data->grid[(data->player_x - MV_SPD) / TILE_SIZE]
		[data->player_y / TILE_SIZE] != '1')
		data->player_x -= MV_SPD;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_player(t_data *img, t_mlx_data *data)
{
	int	x;
	int	y;

	x = -1;
	while (++x < 10)
	{
		y = -1;
		while (++y < 10)
			my_mlx_pixel_put(&(*img), data->player_x + x,
				data->player_y + y, 0x0000FF00);
	}
}

void	draw_square(t_data *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (++i < TILE_SIZE - 1)
	{
		j = 1;
		while (++j < TILE_SIZE - 1)
			my_mlx_pixel_put(&(*img), x * TILE_SIZE + i, y * TILE_SIZE + j, color);
	}
}

void	draw_grid(t_data *img, t_mlx_data *data)
{
	int	x;
	int	y;

	x = -1;
	while (data->grid[++x])
	{
		y = -1;
		while (data->grid[x][++y])
		{
			if (data->grid[x][y] == '1')
				draw_square(img, x, y, 0x000000FF);
			else if (data->grid[x][y] == '0')
				draw_square(img, x, y, 0xFF000000);
		}
	}
}

int	display(t_mlx_data *data)
{
	int		x;
	int		y;
	t_data	*img;

	img = data->img_ptr;
	x = -1;
	y = -1;
	while (++x < 500)
	{
		y = -1;
		while (++y < 500)
			my_mlx_pixel_put(&(*img), x, y, 0x00FF0000);
	}
	draw_grid(img, data);
	draw_player(img, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img->img, 0, 0);
	return (0);
}

void	init(t_mlx_data *data)
{
	data->player_x = 60;
	data->player_y = 320;
	data->img_ptr = malloc(sizeof(t_data));
	data->mlx_ptr = mlx_init();
	data->size_x_window = 500;
	data->size_y_window = 500;
	data->win_ptr = mlx_new_window
		(data->mlx_ptr, data->size_x_window, data->size_y_window, "SO_LONG");
}

void	init_img(t_mlx_data *data)
{
	data->img_ptr->img = mlx_new_image(data->mlx_ptr, 500, 500);
	data->img_ptr->addr = mlx_get_data_addr(data->img_ptr->img,
			&data->img_ptr->bits_per_pixel, &data->img_ptr->line_length,
			&data->img_ptr->endian);
}

void	setup_grid(t_mlx_data *data)
{
	int	y;
	int	i;

	y = 11;
	data->grid = malloc(sizeof(char *) * y);
	data->grid[0] = strdup("1111111111");
	data->grid[1] = strdup("1000000001");
	data->grid[2] = strdup("1000001001");
	data->grid[3] = strdup("1000001001");
	data->grid[4] = strdup("1000001001");
	data->grid[5] = strdup("1000001001");
	data->grid[6] = strdup("1000001001");
	data->grid[7] = strdup("1000001001");
	data->grid[8] = strdup("1000001001");
	data->grid[9] = strdup("1111111111");
	data->grid[10] = NULL;
}

int	main(void)
{
	t_mlx_data	data;

	setup_grid(&data);
	init(&data);
	init_img(&data);
	mlx_loop_hook(data.mlx_ptr, display, &data);
	mlx_hook(data.win_ptr, 17, 0, close_cross, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, handle_key, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
