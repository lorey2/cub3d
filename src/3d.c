/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:37:19 by lorey             #+#    #+#             */
/*   Updated: 2025/04/14 04:05:53 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_wall_params(t_mlx_data *data, double *p_dist, \
				double *d_plane, double *p_height);
static void	calculate_draw_limits(double p_height, \
				int *ds_clamped, int *de_clamped, int *true_ds);
static void	draw_wall_slice(t_mlx_data *data, int x, int ds_clamped, \
				int de_clamped, double p_height, int true_ds);
static void	calculate_fc_ray_params(t_mlx_data *data, int x, \
				double *ray_dx, double *ray_dy, double fov_rad_h);
static void	draw_floor_slice(t_mlx_data *data, int x, int de_clamped, \
				double ray_dx, double ray_dy, double d_plane);
static void	draw_ceiling_slice(t_mlx_data *data, int x, int ds_clamped, \
				double ray_dx, double ray_dy, double d_plane);

/**
 * @brief Calculates the color for a specific vertical pixel (`index`) on a wall slice
 * by sampling the corresponding texture (`data->img_ptr->selected`).
 * @param data Pointer to the main MLX data structure.
 * @param index The current vertical pixel coordinate (y) being drawn on the screen.
 * @param proj_slice_height The calculated projected height of the wall slice on the screen.
 * @return The integer color value sampled from the texture.
 *
 * Determines the texture's y-coordinate based on the pixel's position relative to the
 * projected wall height and the texture's height. Handles clamping the texture y-coordinate
 * to stay within bounds. Uses the pre-calculated `data->textu_x` for the texture's x-coordinate.
 */
int color_y(t_mlx_data *data, int index, double proj_slice_height)
{
	int		x;
	int		y;
	int		color;
	int		pixel_index;
	double	ratio;

	if (!data->img_ptr->selected)
		return (0);
	x = data->textu_x;
	ratio = (double)(index - data->start) / proj_slice_height;
	y = ratio * data->img_ptr->selected->height;
	if (y < 0)
		y = 0;
	if (y >= data->img_ptr->selected->height)
		y = data->img_ptr->selected->height - 1;
	pixel_index = y * data->img_ptr->selected->line_length + x
		* (data->img_ptr->selected->bits_per_pixel / 8);
	color = *(int *)(data->img_ptr->selected->addr + pixel_index);
	return (color);
}

/**
 * @brief Retrieves the color of a pixel from a given texture at specified coordinates (`tex_x`, `tex_y`).
 * @param texture Pointer to the texture data structure (`t_data`).
 * @param tex_x The x-coordinate within the texture.
 * @param tex_y The y-coordinate within the texture.
 * @return The integer color value from the texture, or BLACK if texture is invalid or coordinates are out of bounds.
 *
 * Handles texture wrapping (tiling) using the modulo operator. Ensures coordinates are positive after wrapping.
 * Performs safety checks for null pointers and invalid texture addresses. Calculates the memory offset
 * for the pixel and returns its color.
 */
int	get_texture_pixel(t_data *texture, int tex_x, int tex_y)
{
	char	*pixel_addr;
	int		color;

	if (!texture || !texture->addr)
		return (BLACK);
	tex_x = tex_x % texture->width;
	tex_y = tex_y % texture->height;
	if (tex_x < 0)
		tex_x += texture->width;
	if (tex_y < 0)
		tex_y += texture->height;
	if (tex_x < 0 || tex_x >= texture->width || \
		tex_y < 0 || tex_y >= texture->height)
		return (BLACK);
	pixel_addr = texture->addr + (tex_y * texture->line_length + \
		tex_x * (texture->bits_per_pixel / 8));
	color = *(int *)pixel_addr;
	return (color);
}

/**
 * @brief Calculates parameters needed for drawing a wall slice.
 * @param data Pointer to the main MLX data structure.
 * @param p_dist Pointer to store the calculated perpendicular distance to the wall.
 * @param d_plane Pointer to store the calculated distance to the projection plane.
 * @param p_height Pointer to store the calculated projected height of the wall slice.
 *
 * Computes the perpendicular distance (`p_dist`) to the wall hit, correcting for fisheye distortion.
 * Calculates the distance to the projection plane (`d_plane`) based on the screen width and FOV.
 * Determines the height (`p_height`) the wall slice should have on the screen based on these distances
 * and the defined `TILE_SIZE`. Includes safety checks for minimum distance and near-zero FOV tangent.
 */
static void	calculate_wall_params(t_mlx_data *data, double *p_dist, \
					double *d_plane, double *p_height)
{
	double	fov_rad_half;

	*p_dist = data->best * cos(data->angle - data->angle_bkp);
	if (*p_dist < 0.0001)
		*p_dist = 0.0001;
	fov_rad_half = (FOV * M_PI / 180.0) / 2.0;
	if (fabs(tan(fov_rad_half)) < TOLERANCE)
		*d_plane = 1.0 / TOLERANCE;
	else
		*d_plane = (SIZE_3D_IMG_X / 2.0) / tan(fov_rad_half);
	*p_height = (TILE_SIZE / *p_dist) * *d_plane;
}

/**
 * @brief Calculates the vertical drawing limits for a wall slice on the screen.
 * @param data Pointer to the main MLX data structure (used for screen height).
 * @param p_height The calculated projected height of the wall slice.
 * @param ds_clamped Pointer to store the clamped starting y-coordinate for drawing.
 * @param de_clamped Pointer to store the clamped ending y-coordinate for drawing.
 * @param true_ds Pointer to store the potentially unclipped starting y-coordinate (for texture mapping).
 *
 * Determines the theoretical top (`draw_start_y`) and bottom (`draw_end_y`) screen y-coordinates
 * for the wall slice based on its projected height (`p_height`) and the screen center.
 * Clamps these coordinates (`ds_clamped`, `de_clamped`) to ensure they stay within the screen boundaries
 * (0 to `SIZE_3D_IMG_Y`). Stores the original, potentially off-screen `draw_start_y` in `true_ds`,
 * which is needed for correct vertical texture mapping calculation in `color_y`.
 */
static void	calculate_draw_limits(double p_height, \
								int *ds_clamped, int *de_clamped, int *true_ds)
{
	int	draw_start_y;
	int	draw_end_y;

	draw_start_y = (int)(SIZE_3D_IMG_Y / 2.0 - p_height / 2.0);
	draw_end_y = (int)(SIZE_3D_IMG_Y / 2.0 + p_height / 2.0);
	*true_ds = draw_start_y;
	*ds_clamped = draw_start_y;
	if (*ds_clamped < 0)
		*ds_clamped = 0;
	*de_clamped = draw_end_y;
	if (*de_clamped >= (int)SIZE_3D_IMG_Y)
		*de_clamped = (int)SIZE_3D_IMG_Y;
}

/**
 * @brief Draws a single vertical slice (column `x`) of the textured wall.
 * @param data Pointer to the main MLX data structure.
 * @param x The horizontal screen coordinate (column index) being drawn.
 * @param ds_clamped The clamped starting y-coordinate on the screen.
 * @param de_clamped The clamped ending y-coordinate on the screen.
 * @param p_height The projected height of the wall slice.
 * @param true_ds The unclipped starting y-coordinate (used by `color_y`).
 *
 * Iterates vertically from `ds_clamped` to `de_clamped`. For each pixel `y` in this range,
 * it calls `color_y` (passing `true_ds` implicitly via `data->start`) to get the correct
 * texture color based on the vertical position on the wall. It then draws this color
 * onto the target image (`data->img_ptr->raycast`) at coordinates (`x`, `y`).
 */
static void	draw_wall_slice(t_mlx_data *data, int x, int ds_clamped, \
					int de_clamped, double p_height, int true_ds)
{
	int	y;
	int	color;

	y = ds_clamped;
	data->start = true_ds;
	while (y < de_clamped)
	{
		color = color_y(data, y, p_height);
		my_mlx_pixel_put(data->img_ptr->game, x, y, color);
		y++;
	}
}

/**
 * @brief Calculates the ray direction vector components for floor and ceiling casting.
 * @param data Pointer to the main MLX data structure.
 * @param x The horizontal screen coordinate (column index) being processed.
 * @param ray_dx Pointer to store the calculated x-component of the ray direction.
 * @param ray_dy Pointer to store the calculated y-component of the ray direction.
 * @param fov_rad_h The horizontal Field of View half-angle in radians.
 *
 * Determines the direction vector (`ray_dx`, `ray_dy`) in world space for the ray
 * passing through the screen column `x`. This is achieved by combining the player's
 * current direction vector with the camera plane vector, scaled according to the
 * column's position relative to the screen center (`camera_x`). This direction is
 * essential for projecting screen pixels onto the floor and ceiling planes.
 */
static void	calculate_fc_ray_params(t_mlx_data *data, int x, \
						double *ray_dx, double *ray_dy, double fov_rad_h)
{
	double	player_dir_x;
	double	player_dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;

	player_dir_x = cos(data->angle_bkp);
	player_dir_y = sin(data->angle_bkp);
	plane_x = -player_dir_y * tan(fov_rad_h);
	plane_y = player_dir_x * tan(fov_rad_h);
	camera_x = 2.0 * x / SIZE_3D_IMG_X - 1.0;
	*ray_dx = player_dir_x + plane_x * camera_x;
	*ray_dy = player_dir_y + plane_y * camera_x;
}

/**
 * @brief Draws the textured floor for a single vertical slice (column `x`).
 * @param data Pointer to the main MLX data structure.
 * @param x The horizontal screen coordinate (column index) being drawn.
 * @param de_clamped The y-coordinate where the floor starts (bottom of the wall).
 * @param ray_dx The x-component of the ray direction for this column.
 * @param ray_dy The y-component of the ray direction for this column.
 * @param d_plane The distance to the projection plane.
 *
 * Iterates vertically from the bottom of the wall (`de_clamped`) down to the bottom of the screen.
 * For each screen pixel `y` in this range:
 * 1. Calculates the real-world distance (`current_dist`) to the floor point visible at this pixel using perspective projection.
 * 2. Determines the world coordinates (`floor_x`, `floor_y`) of this floor point.
 * 3. Converts these world coordinates into texture coordinates (`tex_x`, `tex_y`) for the floor texture (`data->img_ptr->dirt`), handling wrapping/tiling.
 * 4. Retrieves the color from the floor texture using `get_texture_pixel`.
 * 5. Draws the pixel onto the raycast image buffer.
 * Includes a check for a valid floor texture.
 */
static void	draw_floor_slice(t_mlx_data *data, int x, int de_clamped, \
							double ray_dx, double ray_dy, double d_plane)
{
	int		y;
	double	current_dist;
	double	floor_x;
	double	floor_y;
	int		tex_x;
	int		tex_y;
	int		floor_color;
	t_data	*selected;

	selected = data->img_arr->floor_img[(int)(((long long)data->frame_nbr * data->img_arr->floor_img[0]->frame_nbr) / FPS)];
	if (!selected || !selected->addr)
		return ;
	y = de_clamped;
	while (y < (int)SIZE_3D_IMG_Y)
	{
		current_dist = (0.5 * TILE_SIZE * d_plane) / (y - SIZE_3D_IMG_Y / 2.0);
		floor_x = data->player_x + ray_dx * current_dist;
		floor_y = data->player_y + ray_dy * current_dist;
		tex_x = (int)((floor_x / TILE_SIZE - floor(floor_x / TILE_SIZE)) * \
				selected->width);
		tex_y = (int)((floor_y / TILE_SIZE - floor(floor_y / TILE_SIZE)) * \
				selected->height);
		floor_color = get_texture_pixel(selected, tex_x, tex_y);
		my_mlx_pixel_put(data->img_ptr->game, x, y, floor_color);
		y++;
	}
}

/**
 * @brief Draws the textured ceiling for a single vertical slice (column `x`).
 * @param data Pointer to the main MLX data structure.
 * @param x The horizontal screen coordinate (column index) being drawn.
 * @param ds_clamped The y-coordinate where the ceiling ends (top of the wall).
 * @param ray_dx The x-component of the ray direction for this column.
 * @param ray_dy The y-component of the ray direction for this column.
 * @param d_plane The distance to the projection plane.
 *
 * Iterates vertically from the top of the screen (y=0) down to the top of the wall (`ds_clamped`).
 * For each screen pixel `y` in this range:
 * 1. Calculates the real-world distance (`current_dist`) to the ceiling point visible at this pixel using perspective projection.
 * 2. Determines the world coordinates (`ceil_x`, `ceil_y`) of this ceiling point.
 * 3. Converts these world coordinates into texture coordinates (`tex_x`, `tex_y`) for the ceiling texture (`data->img_ptr->diam`), handling wrapping/tiling.
 * 4. Retrieves the color from the ceiling texture using `get_texture_pixel`.
 * 5. Draws the pixel onto the raycast image buffer.
 * Includes a check for a valid ceiling texture.
 */
static void	draw_ceiling_slice(t_mlx_data *data, int x, int ds_clamped, \
								double ray_dx, double ray_dy, double d_plane)
{
	int		y;
	double	current_dist;
	double	ceil_x;
	double	ceil_y;
	int		tex_x;
	int		tex_y;
	int		ceil_color;
	t_data	*selected;

	selected = data->img_arr->ceiling_img[(int)(((long long)data->frame_nbr * data->img_arr->ceiling_img[0]->frame_nbr) / FPS)];
	if (!selected || !selected->addr)
		return ;
	y = 0;
	while (y < ds_clamped)
	{
		current_dist = (0.5 * TILE_SIZE * d_plane) / (SIZE_3D_IMG_Y / 2.0 - y);
		ceil_x = data->player_x + ray_dx * current_dist;
		ceil_y = data->player_y + ray_dy * current_dist;
		tex_x = (int)((ceil_x / TILE_SIZE - floor(ceil_x / TILE_SIZE)) * \
				selected->width);
		tex_y = (int)((ceil_y / TILE_SIZE - floor(ceil_y / TILE_SIZE)) * \
				selected->height);
		ceil_color = get_texture_pixel(selected, tex_x, tex_y);
		my_mlx_pixel_put(data->img_ptr->game, x, y, ceil_color);
		y++;
	}
}

/**
 * @brief Renders a complete vertical slice (column `x`) of the 3D scene.
 * @param data Pointer to the main MLX data structure.
 * @param x The horizontal screen coordinate (column index) to render.
 *
 * This function orchestrates the rendering process for a single column `x` of the screen.
 * 1. Calculates wall parameters (distance, height, projection plane distance).
 * 2. Determines the vertical drawing limits (start/end y-coordinates) for the wall slice, clamping them to the screen.
 * 3. Draws the textured wall slice within these limits.
 * 4. Calculates the ray direction vector needed for floor and ceiling casting.
 * 5. Draws the textured floor slice below the wall.
 * 6. Draws the textured ceiling slice above the wall.
 * This function effectively combines the results of raycasting (finding `data->best`, `data->angle`, etc., presumably done before calling this)
 * with perspective projection and texture mapping to create one column of the final 3D image.
 */
void draw_3d(t_mlx_data *data, int x)
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

	calculate_wall_params(data, &perp_dist, &dist_to_proj_plane, \
						&proj_slice_height);
	calculate_draw_limits(proj_slice_height, &draw_start_y_clamped, \
						&draw_end_y_clamped, &true_draw_start_y);
	draw_wall_slice(data, x, draw_start_y_clamped, draw_end_y_clamped, \
					proj_slice_height, true_draw_start_y);
	fov_rad_half = (FOV * M_PI / 180.0) / 2.0;
	calculate_fc_ray_params(data, x, &ray_dir_x, &ray_dir_y, fov_rad_half);
	draw_floor_slice(data, x, draw_end_y_clamped, ray_dir_x, ray_dir_y, \
					dist_to_proj_plane);
	draw_ceiling_slice(data, x, draw_start_y_clamped, ray_dir_x, ray_dir_y, \
					dist_to_proj_plane);
}
