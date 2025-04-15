/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:45:58 by lorey             #+#    #+#             */
/*   Updated: 2025/04/15 02:25:46 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx_linux/mlx.h"
# include "../libft/include/libft.h"
# include <stdbool.h>
# include <bits/types/struct_timeval.h>
# include <X11/keysym.h>
# include <sys/time.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <string.h>

# define RED          0x00FF0000  // Red: R=255, G=0, B=0
# define GREEN        0x0000FF00  // Green: R=0, G=255, B=0
# define BLUE         0x000000FF  // Blue: R=0, G=0, B=255
# define WHITE        0x00FFFFFF  // White: R=255, G=255, B=255
# define BLACK        0x00000000  // Black: R=0, G=0, B=0
# define YELLOW       0x00FFFF00  // Yellow: R=255, G=255, B=0
# define CYAN         0x0000FFFF  // Cyan: R=0, G=255, B=255
# define MAGENTA      0x00FF00FF  // Magenta: R=255, G=0, B=255
# define GRAY         0x00808080  // Gray: R=128, G=128, B=128
# define DARK_GRAY    0x00404040  // Gray: R=64, G=64, B=64
# define BROWN        0x00A52A2A  // Brown: R=165, G=42, B=42
# define SADDLE_BROWN 0x008B4513 // R=139, G=69, B=19
# define SIENNA       0x00A0522D // R=160, G=82, B=45
# define MAROON       0x00800000 // R=128, G=0, B=0
# define ORANGE       0x00FFA500  // Orange: R=255, G=165, B=0
# define PURPLE       0x00800080  // Purple: R=128, G=0, B=128
# define PINK         0x00FFC0CB  // Pink: R=255, G=192, B=203
# define TEAL         0x00008080  // Teal: R=0, G=128, B=128
# define OLIVE        0x00808000  // Olive: R=128, G=128, B=0
# define NAVY         0x00000080  // Navy: R=0, G=0, B=128
# define SILVER       0x00C0C0C0  // Silver: R=192, G=192, B=192
# define GOLD         0x00FFD700  // Gold: R=255, G=215, B=0
# define SKYBLUE      0x0087CEEB  // Sky Blue: R=135, G=206, B=235
# define VIOLET       0x00EE82EE  // Violet: R=238, G=130, B=238
# define DARKGREEN    0x00006400  // Dark Green: R=0, G=100, B=0
# define INDIGO       0x004B0082  // Indigo: R=75, G=0, B=130
# define BEIGE        0x00F5F5DC  // Beige: R=245, G=245, B=220

// TODO: WHEN I SAY WILL CHANGE I MEAN THAT WONT BE A DEFINE BUT A PARSED VALUE

//////////////////
//player related//
//////////////////
# define MV_SPD			3.0		//nbr of pxl moved each frame
# define MOUSE_SENSI	-0.003	//mouse sensi
# define SAFETY			5.0		//in colision a margin between player and wall
# define INIT_ANGLE		M_PI_4	//initial angle of player      TODO: WILL CHANGE
# define PLAYER_INIT_X	100		//position initial of player   TODO: WILL CHANGE
# define PLAYER_INIT_Y	400     //                             TODO: WILL CHANGE
///////////////////
//minimap related//
///////////////////
# define SIZE_MAP_X		500		//size of minimap img
# define SIZE_MAP_Y		500		//
# define POS_MAP_X		0		//position of minimap
# define POS_MAP_Y		0		//
//////////////
//3d related//
//////////////
# define SIZE_3D_IMG_X	1000.0	//size of the 3d img
# define SIZE_3D_IMG_Y	1000.0	//
# define POS_3D_X		500		//position of the map img in screen
# define POS_3D_Y		0		//
/////////////////
//general/other//
/////////////////
# define TILE_SIZE		50.0	//real size of a minimap tile
# define MAX_RAY_STEPS	20.0	//nbr of intersection max with grid
# define TOLERANCE		0.02	//to avoid infinity in trigo
# define FOV			50.0	//in degree field of wiew
# define RAY_NUMBER		1000.0	//number of rays. Best equal to SIZE_3D_IMG_X
# define FPS			60.0	//to avoid framerate jump the fps is capped

# define WIN_SIZE_X	1500	// TODO: CHANGE THAT
# define WIN_SIZE_Y	1000	// TODO: CHANGE THAT

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	int		frame_nbr;
}				t_data;

typedef struct s_tex_name
{
	char	**north_tex_name;
	char	**south_tex_name;
	char	**west_tex_name;
	char	**east_tex_name;
	char	**floor_tex_name;
	char	**ceiling_tex_name;
	char	**door_tex_name;
}				t_tex_name;

typedef struct s_tex_img_array
{
	t_data	**north_img;
	t_data	**south_img;
	t_data	**west_img;
	t_data	**east_img;
	t_data	**floor_img;
	t_data	**ceiling_img;
	t_data	**door_img;
}				t_tex_img_array;

typedef struct s_key
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	q;
	bool	e;
	int		mouse_x;
	int		old_mouse_x;
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

typedef struct s_img_ptr
{
	t_data			*minimap;
	t_data			*game;
	t_data			*selected;
}				t_img_ptr;

typedef struct s_mlx_data
{
	bool			is_open;
	bool			is_door_hor;
	bool			is_door_ver;
	int				frame_nbr;
	int				textu_x;
	int				diff;
	int				start;
	struct timeval	last_frame_time;
	t_tex_img_array	*img_arr;
	t_tex_name		*text_arr;
	t_key			*key;
	t_dline			*l;
	t_img_ptr		*img_ptr;
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
void			init_img(t_mlx_data *data, t_img_ptr *img);
void			setup_grid(t_mlx_data *data);
//hook
void			handle_key(t_mlx_data *data);
int				key_pressed(int keysym, t_mlx_data *data);
int				display(t_mlx_data *data);
int				change_angle(t_mlx_data *data);
int				mouse_move(int x, int y, t_mlx_data *data);
//draw
void			draw_player(t_data *img, t_mlx_data *data);
void			draw_square(t_data *img, int x, int y, int color);
void			draw_grid(t_data *img, t_mlx_data *data);
void			draw_line(t_mlx_data *data, t_dline *l);
//utils
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			err(char *str);
void			safe_free(void **ptr);
//draw_best_line
void			draw_best_line(t_mlx_data *data);
//3d
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
void			load_map(char *map_file, t_mlx_data *data);
void			check_map(char *map_file, t_mlx_data *data);

#endif
