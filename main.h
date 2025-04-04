/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lo>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 23:27:17 by lorey             #+#    #+#             */
/*   Updated: 2025/04/04 03:13:01 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "mlx_linux/mlx.h"
# include <bits/types/struct_timeval.h>
# include <X11/keysym.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

# define MALLOC_ERROR	1
# define MV_SPD			5
# define TILE_SIZE		50

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
	char			**grid;
}				t_mlx_data;

#endif
