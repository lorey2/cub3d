/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:41:56 by lorey             #+#    #+#             */
/*   Updated: 2025/04/12 01:58:03 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_wall_params(t_mlx_data *data, double *p_dist, \
				double *d_plane, double *p_height);
static void	calculate_draw_limits(t_mlx_data *data, double p_height, \
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
    int      x;
    int      y;
    int      color;
    int      pixel_index;
    double   ratio;

    if (!data->img_ptr->selected)
        return (0); // Return black or default color if no texture selected
    x = data->textu_x;
    // Calculate the vertical ratio on the wall slice
    ratio = (double)(index - data->start) / proj_slice_height;
    // Map the ratio to the texture's height
    y = ratio * data->img_ptr->selected->height;
    // Clamp the texture y-coordinate
    if (y < 0)
        y = 0;
    if (y >= data->img_ptr->selected->height)
        y = data->img_ptr->selected->height - 1;
    // Calculate the pixel index in the texture's linear memory buffer
    pixel_index = y * data->img_ptr->selected->line_length + x
                  * (data->img_ptr->selected->bits_per_pixel / 8);
    // Retrieve the color from the texture data
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
int get_texture_pixel(t_data *texture, int tex_x, int tex_y)
{
    char    *pixel_addr;
    int      color;

    // Safety check for texture validity
    if (!texture || !texture->addr)
        return (BLACK); // Return a default color (e.g., black)

    // Apply texture wrapping (tiling)
    tex_x = tex_x % texture->width;
    tex_y = tex_y % texture->height;
    // Ensure coordinates are non-negative after modulo
    if (tex_x < 0)
        tex_x += texture->width;
    if (tex_y < 0)
        tex_y += texture->height;

    // Redundant boundary check (good practice, though modulo should handle it)
    if (tex_x < 0 || tex_x >= texture->width || \
        tex_y < 0 || tex_y >= texture->height)
        return (BLACK); // Out of bounds

    // Calculate the address of the desired pixel in the texture's memory buffer
    pixel_addr = texture->addr + (tex_y * texture->line_length + \
                                  tex_x * (texture->bits_per_pixel / 8));
    // Retrieve the color value
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
static void calculate_wall_params(t_mlx_data *data, double *p_dist, \
                                 double *d_plane, double *p_height)
{
    double   fov_rad_half;

    // Calculate perpendicular distance (corrects fisheye)
    *p_dist = data->best * cos(data->angle - data->angle_bkp);
    // Prevent division by zero or near-zero distances
    if (*p_dist < 0.0001)
        *p_dist = 0.0001;

    // Calculate distance to projection plane based on FOV and screen width
    fov_rad_half = (FOV * M_PI / 180.0) / 2.0;
    if (fabs(tan(fov_rad_half)) < TOLERANCE) // Avoid division by zero/very small number
        *d_plane = 1.0 / TOLERANCE; // Use a large distance instead
    else
        *d_plane = (SIZE_3D_IMG_X / 2.0) / tan(fov_rad_half);

    // Calculate projected wall height on the screen
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
static void calculate_draw_limits(t_mlx_data *data, double p_height, \
                                 int *ds_clamped, int *de_clamped, int *true_ds)
{
    int   draw_start_y;
    int   draw_end_y;

    // Calculate theoretical start and end y-coordinates centered on the screen
    draw_start_y = (int)(SIZE_3D_IMG_Y / 2.0 - p_height / 2.0);
    draw_end_y = (int)(SIZE_3D_IMG_Y / 2.0 + p_height / 2.0);

    // Store the unclipped start position (needed for texture mapping)
    *true_ds = draw_start_y;

    // Clamp the drawing start position to the top of the screen
    *ds_clamped = draw_start_y;
    if (*ds_clamped < 0)
        *ds_clamped = 0;

    // Clamp the drawing end position to the bottom of the screen
    *de_clamped = draw_end_y;
    if (*de_clamped >= (int)SIZE_3D_IMG_Y)
        *de_clamped = (int)SIZE_3D_IMG_Y; // Use < SIZE_3D_IMG_Y if indexing starts at 0
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
static void draw_wall_slice(t_mlx_data *data, int x, int ds_clamped, \
                           int de_clamped, double p_height, int true_ds)
{
    int   y;
    int   color;

    y = ds_clamped;
    data->start = true_ds; // Pass the unclipped start Y for correct texture mapping in color_y
    while (y < de_clamped)
    {
        // Get the texture color for the current pixel
        color = color_y(data, y, p_height);
        // Draw the pixel onto the raycast image buffer
        my_mlx_pixel_put(data->img_ptr->raycast, x, y, color);
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
static void calculate_fc_ray_params(t_mlx_data *data, int x, \
                                   double *ray_dx, double *ray_dy, double fov_rad_h)
{
    double   player_dir_x;
    double   player_dir_y;
    double   plane_x; // Camera plane x-component
    double   plane_y; // Camera plane y-component
    double   camera_x; // X-coordinate on the camera plane (-1 to 1)

    // Player's direction vector
    player_dir_x = cos(data->angle_bkp);
    player_dir_y = sin(data->angle_bkp);

    // Camera plane vector (perpendicular to direction, scaled by tan(FOV/2))
    plane_x = -player_dir_y * tan(fov_rad_h);
    plane_y = player_dir_x * tan(fov_rad_h);

    // Calculate the position on the camera plane for the current screen column x
    // Maps screen x (0 to SIZE_3D_IMG_X) to camera plane x (-1 to 1)
    camera_x = 2.0 * x / SIZE_3D_IMG_X - 1.0;

    // Calculate the final ray direction vector for this column
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
static void draw_floor_slice(t_mlx_data *data, int x, int de_clamped, \
                            double ray_dx, double ray_dy, double d_plane)
{
    int      y;
    double   current_dist; // Distance from camera to the floor point
    double   floor_x;      // World x-coordinate of the floor point
    double   floor_y;      // World y-coordinate of the floor point
    int      tex_x;        // Texture x-coordinate
    int      tex_y;        // Texture y-coordinate
    int      floor_color;

    // Check if floor texture is valid
    if (!data->img_ptr->dirt || !data->img_ptr->dirt->addr)
        return; // Or draw solid color fallback in a separate loop/function

    y = de_clamped; // Start drawing from below the wall
    while (y < (int)SIZE_3D_IMG_Y)
    {
        // Calculate distance to the floor point corresponding to this screen pixel y
        // Formula derived from perspective projection (assuming camera height = 0.5 * TILE_SIZE)
        current_dist = (0.5 * TILE_SIZE * d_plane) / (y - SIZE_3D_IMG_Y / 2.0);

        // Calculate world coordinates of the floor point
        floor_x = data->player_x + ray_dx * current_dist;
        floor_y = data->player_y + ray_dy * current_dist;

        // Calculate texture coordinates (with tiling)
        // Takes the fractional part of the world coordinate scaled by texture dimension
        tex_x = (int)((floor_x / TILE_SIZE - floor(floor_x / TILE_SIZE)) * \
                      data->img_ptr->dirt->width);
        tex_y = (int)((floor_y / TILE_SIZE - floor(floor_y / TILE_SIZE)) * \
                      data->img_ptr->dirt->height);

        // Get the color from the floor texture
        floor_color = get_texture_pixel(data->img_ptr->dirt, tex_x, tex_y);

        // Draw the floor pixel
        my_mlx_pixel_put(data->img_ptr->raycast, x, y, floor_color);
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
static void draw_ceiling_slice(t_mlx_data *data, int x, int ds_clamped, \
                                double ray_dx, double ray_dy, double d_plane)
{
    int      y;
    double   current_dist; // Distance from camera to the ceiling point
    double   ceil_x;       // World x-coordinate of the ceiling point
    double   ceil_y;       // World y-coordinate of the ceiling point
    int      tex_x;        // Texture x-coordinate
    int      tex_y;        // Texture y-coordinate
    int      ceil_color;

    // Check if ceiling texture is valid
    if (!data->img_ptr->diam || !data->img_ptr->diam->addr)
        return; // Or draw solid color fallback

    y = 0; // Start drawing from the top of the screen
    while (y < ds_clamped) // Stop at the top of the wall
    {
        // Calculate distance to the ceiling point corresponding to this screen pixel y
        // Formula derived from perspective projection (assuming camera height = 0.5 * TILE_SIZE)
        current_dist = (0.5 * TILE_SIZE * d_plane) / (SIZE_3D_IMG_Y / 2.0 - y);

        // Calculate world coordinates of the ceiling point
        ceil_x = data->player_x + ray_dx * current_dist;
        ceil_y = data->player_y + ray_dy * current_dist;

        // Calculate texture coordinates (with tiling)
        tex_x = (int)((ceil_x / TILE_SIZE - floor(ceil_x / TILE_SIZE)) * \
                      data->img_ptr->diam->width);
        tex_y = (int)((ceil_y / TILE_SIZE - floor(ceil_y / TILE_SIZE)) * \
                      data->img_ptr->diam->height);

        // Get the color from the ceiling texture
        ceil_color = get_texture_pixel(data->img_ptr->diam, tex_x, tex_y);

        // Draw the ceiling pixel
        my_mlx_pixel_put(data->img_ptr->raycast, x, y, ceil_color);
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
    double   perp_dist;          // Perpendicular distance to the wall
    double   dist_to_proj_plane; // Distance from camera to projection plane
    double   proj_slice_height;  // Height of the wall slice on screen
    int      draw_start_y_clamped; // Clamped top Y for wall drawing
    int      draw_end_y_clamped;   // Clamped bottom Y for wall drawing
    int      true_draw_start_y;  // Unclamped top Y for wall texture mapping
    double   ray_dir_x;          // Ray direction x-component (for floor/ceiling)
    double   ray_dir_y;          // Ray direction y-component (for floor/ceiling)
    double   fov_rad_half;       // FOV half-angle in radians

    // Calculate wall distance, projection plane distance, and projected wall height
    calculate_wall_params(data, &perp_dist, &dist_to_proj_plane, \
                          &proj_slice_height);

    // Determine the screen y-coordinates for drawing the wall slice
    calculate_draw_limits(data, proj_slice_height, &draw_start_y_clamped, \
                          &draw_end_y_clamped, &true_draw_start_y);

    // Draw the textured wall slice
    draw_wall_slice(data, x, draw_start_y_clamped, draw_end_y_clamped, \
                    proj_slice_height, true_draw_start_y);

    // Prepare for floor and ceiling casting
    fov_rad_half = (FOV * M_PI / 180.0) / 2.0;
    calculate_fc_ray_params(data, x, &ray_dir_x, &ray_dir_y, fov_rad_half);

    // Draw the textured floor slice below the wall
    draw_floor_slice(data, x, draw_end_y_clamped, ray_dir_x, ray_dir_y, \
                     dist_to_proj_plane);

    // Draw the textured ceiling slice above the wall
    draw_ceiling_slice(data, x, draw_start_y_clamped, ray_dir_x, ray_dir_y, \
                       dist_to_proj_plane);
}
