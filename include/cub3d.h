/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:45:58 by lorey             #+#    #+#             */
/*   Updated: 2025/04/09 14:03:44 by maambuhl         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx_linux/mlx.h"
# include <stdbool.h>
# include <bits/types/struct_timeval.h>
# include <X11/keysym.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <string.h>

# define RED      0x00FF0000  // Red: R=255, G=0, B=0
# define GREEN    0x0000FF00  // Green: R=0, G=255, B=0
# define BLUE     0x000000FF  // Blue: R=0, G=0, B=255
# define WHITE    0x00FFFFFF  // White: R=255, G=255, B=255
# define BLACK    0x00000000  // Black: R=0, G=0, B=0
# define YELLOW   0x00FFFF00  // Yellow: R=255, G=255, B=0
# define CYAN     0x0000FFFF  // Cyan: R=0, G=255, B=255
# define MAGENTA  0x00FF00FF  // Magenta: R=255, G=0, B=255
# define GRAY     0x00808080  // Gray: R=128, G=128, B=128

# define MALLOC_ERROR	1
# define MV_SPD			1.0
# define SAFETY			5.0
# define TILE_SIZE		50.0
# define MAX_RAY_STEPS	20.0
# define TOLERANCE		0.02
# define FOV			70.0
# define RAY_NUMBER		1000.0
# define S_RAY_X		1000.0
# define S_RAY_Y		1000.0
# define FPS			120.0

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_key
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	q;
	bool	e;
}				t_key;

typedef struct s_dline
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				e2;
	int				color;
}				t_dline;

typedef struct s_mlx_data
{
	t_data			*img_ptr;
	t_data			*raycast;
	struct timeval	last_frame_time;
	t_key			*key;
	t_dline			*l;
	double			size_x_window;
	double			size_y_window;
	void			*mlx_ptr;
	void			*win_ptr;
	double			player_x;
	double			player_y;
	double			angle;
	char			**grid;
	double			ray_ver;
	double			ray_hor;
	double			best;
	int				color;
	double			i;
	double			angle_bkp;
	double			j;
	double			next_x;
	double			next_y;
	double			next_s_x;
	double			next_s_y;
}				t_mlx_data;

typedef struct s_linex
{
	int				x;
	int				neg;
	double			col_index;
	double			row_index;
	double			delta_x;
	double			offset;
}				t_linex;

typedef struct s_liney
{
	int				y;
	int				neg;
	double			col_index;
	double			row_index;
	double			delta_y;
	double			offset;
}				t_liney;

//init_setp
void			init(t_mlx_data *data);
void			init_img(t_mlx_data *data);
void			setup_grid(t_mlx_data *data);
//hook
void			handle_key(t_mlx_data *data);
int				key_pressed(int keysym, t_mlx_data *data);
int				display(t_mlx_data *data);
int				change_angle(t_mlx_data *data);
//draw
void			draw_player(t_data *img, t_mlx_data *data);
void			draw_square(t_data *img, int x, int y, int color);
void			draw_grid(t_data *img, t_mlx_data *data);
void			draw_line(t_mlx_data *data, t_dline *l);
//utils
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
//draw_best_line
void			draw_best_line(t_mlx_data *data);
//3d
void			draw_3d_top(t_data *img_3d);
void			draw_3d_bottom(t_data *img_3d);
void			draw_3d(t_mlx_data *data, int ray);
//minimap
void			draw_minimap_background(t_data *img);
void			draw_player(t_data *img, t_mlx_data *data);
void			draw_grid(t_data *img, t_mlx_data *data);
//exit
int				close_cross(t_mlx_data *data);
int				close_esc(int keysym, t_mlx_data *data);
//calcul_rey
int				ver_best_line(t_mlx_data *data, t_linex *ver);
int				hor_best_line(t_mlx_data *data, t_liney *hor);
//parsing
bool			check_map_file(char *map_file);
void			load_map(char *map_file);

#endif
