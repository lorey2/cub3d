/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:45:58 by lorey             #+#    #+#             */
/*   Updated: 2025/04/29 16:09:07 by maambuhl         ###   LAUSANNE.ch       */
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

// WARNING: IF NO NSEO (for debug cause it is checked in parsing) :)

//////////////////
//player related//
//////////////////
# define MV_SPD			3.0		//nbr of pxl moved each frame
# define MOUSE_SENSI	-0.003	//mouse sensi
# define SAFETY			5.0		//in colision a margin between player and wall
# define INIT_ANGLE		M_PI_4	//initial angle of player    WARNING: IF NO NSEO
# define PLAYER_INIT_X	500		//init pos of player         WARNING: IF NO NSEO
# define PLAYER_INIT_Y	500     //                           WARNING: IF NO NSEO
///////////////////
//minimap related//
///////////////////
# define SIZE_MAP_X		500.0		//size of minimap img
# define SIZE_MAP_Y		500.0		//
# define POS_MAP_X		0		//position of minimap
# define POS_MAP_Y		0		//
/////////////////
//general/other//
/////////////////
# define TILE_SIZE		50.0	//real size of a minimap tile
# define MAX_RAY_STEPS	20.0	//nbr of intersection max with grid
# define TOLERANCE		0.02	//to avoid infinity in trigo
# define FOV			50.0	//in degree field of wiew
# define RAY_NUMBER		1000.0	//number of rays. Best equal to SIZE_3D_IMG_X
# define FPS			60.0	//to avoid framerate jump the fps is capped
//////////////
//3d related//
//////////////
# define SIZE_3D_IMG_X	RAY_NUMBER	//size of the 3d img
# define SIZE_3D_IMG_Y	1000.0	//
# define POS_3D_X		500		//position of the map img in screen
# define POS_3D_Y		0		//

# define WIN_SIZE_X	SIZE_3D_IMG_X
# define WIN_SIZE_Y	SIZE_3D_IMG_Y

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
	int		n_size;
	char	**south_tex_name;
	int		s_size;
	char	**west_tex_name;
	int		w_size;
	char	**east_tex_name;
	int		e_size;
	char	**floor_tex_name;
	int		f_size;
	char	**ceiling_tex_name;
	int		c_size;
	char	**door_tex_name;
	int		d_size;
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

typedef struct s_3d_data
{
	double	perp_dist;
	double	dist_to_proj_plane;
	double	proj_slice_height;
	int		draw_start_y_clamped;
	int		draw_end_y_clamped;
	int		true_draw_start_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	fov_rad_half;
}				t_3d_data;

typedef struct s_mlx_data
{
	int				y_size;
	double			mm_ratio;
	int				tile_x_nbr;
	int				tile_y_nbr;
	int				tile_max_nbr;
	bool			is_open;
	bool			is_door_hor;
	bool			is_door_ver;
	int				frame_nbr;
	int				textu_x;
	int				start;
	struct timeval	last_frame_time;
	t_tex_img_array	*img_arr;
	t_tex_name		*text_arr;
	t_key			*key;
	t_dline			*l;
	t_img_ptr		*img_ptr;
	t_3d_data		*data_3d;
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
	double			angle_bkp;
	double			next_s_x;
	double			next_s_y;
	int				color;
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

void			set_all_data_pointer_to_null(t_mlx_data *data);
void			init(t_mlx_data *data);
void			init_img(t_mlx_data *data, t_img_ptr *img);
void			init_texture(t_tex_name *tex);
void			setup_player_pos_angle(t_mlx_data *data);
//hook
void			handle_key(t_mlx_data *data);
int				key_pressed(int keysym, t_mlx_data *data);
int				display(t_mlx_data *data);
int				change_angle(t_mlx_data *data);
int				mouse_move(int x, int y, t_mlx_data *data);
//draw
void			draw_player(t_data *img, t_mlx_data *data);
void			draw_square(t_data *img, int x, int y, t_mlx_data *data);
void			draw_grid(t_data *img, t_mlx_data *data);
void			draw_line(t_mlx_data *data, t_dline *l);
//utils
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			err(char *str, t_mlx_data *data);
void			safe_free(void **ptr);
void			free_everything(t_mlx_data *data);
void			multi_free(char ***point);
int				open_helper(char *map_file, t_mlx_data *data);
//draw_best_line
void			draw_best_line(t_mlx_data *data);
//3d
void			draw_3d(t_mlx_data *data, int ray);
//3d_utils
int				color_y(t_mlx_data *data, int index, double proj_slice_height);
int				get_texture_pixel(t_data *texture, int tex_x, int tex_y);
void			calculate_wall_params(t_mlx_data *data, t_3d_data *data_3d);
void			calculate_draw_limits(t_3d_data *data);
void			calculate_fc_ray_params(t_mlx_data *data,
					int x, t_3d_data *data_3d);
//minimap
void			size_array(t_mlx_data *data);
void			draw_minimap_background(t_data *img, t_mlx_data *data);
void			draw_player(t_data *img, t_mlx_data *data);
void			draw_grid(t_data *img, t_mlx_data *data);
//exit
int				close_cross(t_mlx_data *data);
int				key_released(int keysym, t_mlx_data *data);
//calcul_rey
int				ver_best_line(t_mlx_data *data, t_linex *ver);
int				hor_best_line(t_mlx_data *data, t_liney *hor);
//parsing
char			**load_map(char *map_file, t_mlx_data *data, int line_to_rm);
void			parsing(char *map_file, t_mlx_data *data);
void			check_map(t_mlx_data *data);
//parsing utils
int				check_texture(char **map, t_mlx_data *data);
char			*remove_line_return(char *line);
bool			check_all_texture(t_mlx_data *data);
void			remove_texture_from_map(char **map, int line_to_rm, t_mlx_data *data);
bool			ft_strisspace(char *str);
bool			check_line_sanity(char *line);
void			remove_last_map_line(t_mlx_data *data);
size_t			get_longest_line(t_mlx_data *data);
int				count_map_line(t_mlx_data *data);
char			*create_padding_string(size_t size, t_mlx_data *data);
char			**copy_map(t_mlx_data *data);
int				*get_blank_space(char **map, int *yx);
bool			valid_map_char(char c);
bool			check_wall(char c);
bool			pars_texture(char **split, t_mlx_data *data);
void			print_map(t_mlx_data *data);
//get_color
int				get_color(double player_pos, t_mlx_data *data,
					double offset, t_data *img);
#endif
