/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lo>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 01:03:07 by lorey             #+#    #+#             */
/*   Updated: 2025/04/07 01:44:21 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	change_angle(t_mlx_data *data)
{
	if (data->key->q == true)
	{
		data->angle -= (M_PI / 180);
		if (data->angle < 0)
			data->angle += 2 * M_PI;
	}
	if (data->key->e == true)
	{
		data->angle += (M_PI / 180);
		if (data->angle >= 2 * M_PI)
			data->angle -= 2 * M_PI;
	}
	data->angle_bkp = data->angle;
	return (0);
}

void	set_next_pos(double next_x, double next_y, t_mlx_data *data)
{
	if (data->grid[(int)(next_x / TILE_SIZE)][(int)(next_y / TILE_SIZE)] != '1')
	{
		data->player_x = next_x;
		data->player_y = next_y;
	}
}

int	key_pressed(int keysym, t_mlx_data *data)
{
	if (keysym == XK_w)
		data->key->w = true;
	if (keysym == XK_a)
		data->key->a = true;
	if (keysym == XK_s)
		data->key->s = true;
	if (keysym == XK_d)
		data->key->d = true;
	if (keysym == XK_q)
		data->key->q = true;
	if (keysym == XK_e)
		data->key->e = true;
	return (0);
}

int	handle_key(t_mlx_data *data)
{
	double next_x;
	double next_y;

	if (data->key->w == true)
	{
	
		next_x = data->player_x + MV_SPD * cos(data->angle_bkp);
		next_y = data->player_y + MV_SPD * sin(data->angle_bkp);
		set_next_pos(next_x, next_y, data);
	}
	else if (data->key->s == true)
	{
		next_x = data->player_x - MV_SPD * cos(data->angle_bkp);
		next_y = data->player_y - MV_SPD * sin(data->angle_bkp);
		set_next_pos(next_x, next_y, data);
	}
	else if (data->key->d == true)
	{
		next_x = data->player_x + MV_SPD * cos(data->angle_bkp + M_PI_2);
		next_y = data->player_y + MV_SPD * sin(data->angle_bkp + M_PI_2);
		set_next_pos(next_x, next_y, data);
	}
	else if (data->key->a == true)
	{
		next_x = data->player_x + MV_SPD * cos(data->angle_bkp - M_PI_2);
		next_y = data->player_y + MV_SPD * sin(data->angle_bkp - M_PI_2);
		set_next_pos(next_x, next_y, data);
	}
	return (0);
}

void	draw_rays(t_mlx_data *data)
{
	double	angle_bkp;
	double	angle_delta;
	double	left_most_ray_angle;
	int		i;
	double	fov;
	double	ray_number;

	fov = FOV;
	ray_number = RAY_NUMBER;
	angle_bkp = data->angle;
	angle_delta = (fov / ray_number) * 2 * M_PI / 360;
	left_most_ray_angle = data->angle - ((fov / 2) * ((2 * M_PI) / 360));
	i = 0;
	data->angle = left_most_ray_angle;
	while (++i < RAY_NUMBER)
	{
		draw_best_line(data);
		draw_3d(data, i);
		data->angle += angle_delta;
	}
	data->angle = angle_bkp;
}

int display(t_mlx_data *data)
{
    t_data *minimap_img;
    t_data *img_3d;
    struct timeval current_time;
    static struct timeval last_frame_time;
    double elapsed_time;
    double target_frame_time = 1.0 / 60.0; // Target 60 FPS (adjust as needed)
    
    // Get current time
    gettimeofday(&current_time, NULL);
    
    // Calculate elapsed time since last frame in seconds
    elapsed_time = (current_time.tv_sec - last_frame_time.tv_sec) +
                   (current_time.tv_usec - last_frame_time.tv_usec) / 1000000.0;
    
    // If we're rendering too fast, delay to match target FPS
    if (elapsed_time < target_frame_time) {
        // Convert seconds to microseconds
        usleep((target_frame_time - elapsed_time) * 1000000);
        
        // Update current time after sleeping
        gettimeofday(&current_time, NULL);
    }
    
    // Update last frame time for next iteration
    last_frame_time = current_time;
    
    // Adjust movement speed based on frame time to keep consistent movement
    double time_factor = elapsed_time / target_frame_time;
    data->current_speed = data->base_speed * time_factor;
    
    // Original display code
    minimap_img = data->img_ptr;
    img_3d = data->raycast;
    handle_key(data);
    change_angle(data);
    draw_minimap_background(minimap_img);
    draw_grid(minimap_img, data);
    draw_player(minimap_img, data);
    draw_3d_top(img_3d);
    draw_3d_bottom(img_3d);
    draw_rays(data);
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_3d->img, 500, 0);
    mlx_put_image_to_window(
        data->mlx_ptr, data->win_ptr, minimap_img->img, 0, 0);
    
    return (0);
}
