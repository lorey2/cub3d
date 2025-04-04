/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:45:58 by lorey             #+#    #+#             */
/*   Updated: 2025/04/04 17:35:08 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx_linux/mlx.h"
# include <bits/types/struct_timeval.h>
# include <X11/keysym.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <string.h>

# define MALLOC_ERROR	1
# define MV_SPD			5
# define TILE_SIZE		50
# define PI				3.1415926535

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_mlx_data
{
	t_data			*img_ptr;
	int				size_x_window;
	int				size_y_window;
	void			*mlx_ptr;
	void			*win_ptr;
	int				player_x;
	int				player_y;
	double			angle;
	char			**grid;
}				t_mlx_data;

//init_setp
void			init(t_mlx_data *data);
void			init_img(t_mlx_data *data);
void			setup_grid(t_mlx_data *data);
//hook
int				handle_key(int keysym, t_mlx_data *data);
int				display(t_mlx_data *data);
int				close_cross(t_mlx_data *data);
int 			close_ESC(int keysym, t_mlx_data *data);
//draw
void			draw_player(t_data *img, t_mlx_data *data);
void			draw_square(t_data *img, int x, int y, int color);
void			draw_grid(t_data *img, t_mlx_data *data);
void			draw_line(t_mlx_data *data, int x1, int y1, int x2, int y2, int color);
//utils
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
