/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 18:05:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	init_window_size(t_data *data)
{
	int	screen_w;
	int	screen_h;
	int	calculated_w;
	int	calculated_h;

	mlx_get_screen_size(data->mlx_ptr, &screen_w, &screen_h);
	calculated_w = (int)(screen_w * WINDOW_WIDTH_RATIO);
	calculated_h = (int)(screen_h * WINDOW_HEIGHT_RATIO);
	if (calculated_w < MIN_WINDOW_WIDTH)
		data->graphics.window.width = MIN_WINDOW_WIDTH;
	else if (calculated_w > MAX_WINDOW_WIDTH)
		data->graphics.window.width = MAX_WINDOW_WIDTH;
	else
		data->graphics.window.width = calculated_w;
	if (calculated_h < MIN_WINDOW_HEIGHT)
		data->graphics.window.height = MIN_WINDOW_HEIGHT;
	else if (calculated_h > MAX_WINDOW_HEIGHT)
		data->graphics.window.height = MAX_WINDOW_HEIGHT;
	else
		data->graphics.window.height = calculated_h;
	if (data->graphics.window.width > screen_w - 50)
		data->graphics.window.width = screen_w - 50;
	if (data->graphics.window.height > screen_h - 50)
		data->graphics.window.height = screen_h - 50;
}

void	init_mouse(t_data *data)
{
	data->mouse.left_pressed = 0;
	data->mouse.right_pressed = 0;
	data->mouse.middle_pressed = 0;
	data->mouse.last_x = 0;
	data->mouse.last_y = 0;
	data->mouse.middle_start_x = 0;
	data->mouse.middle_start_y = 0;
}

void	init_keys(t_data *data)
{
	data->keys.up = 0;
	data->keys.down = 0;
	data->keys.left = 0;
	data->keys.right = 0;
	data->keys.ctrl_left = 0;
	data->keys.ctrl_right = 0;
	data->keys.shift_left = 0;
	data->keys.shift_right = 0;
	data->keys.l = 0;
	data->keys.z = 0;
	data->keys.f = 0;
	data->keys.h = 0;
	data->keys.d = 0;
}

void	init_map_config(t_data *data)
{
	data->map_config.line_thickness = 1;
	data->map_config.point_thickness = 0;
	data->map_config.line_color = 0xFFFFFF;
	data->map_config.point_color = 0xFFFFFF;
	data->map_config.style = 0;
}

void	init_camera(t_data *data)
{
	t_camera_context	ctx;

	data->camera.move_speed = 1.0;
	data->camera.zoom_speed = 1.0;
	data->camera.projection = PROJ_ISOMETRIC;
	data->camera.gui_style = 0;
	data->camera.pending_rot_x = 0.0;
	data->camera.pending_rot_y = 0.0;
	data->camera.z_scale = DEFAULT_Z_SCALE;
	data->camera.frustum_margin = DEFAULT_FRUSTUM_MARGIN;
	data->camera.dampening_threshold = DEFAULT_DAMPENING_THRESHOLD;
	data->camera.spline_segments = DEFAULT_SPLINE_SEGMENTS;
	data->camera.use_z_divisor = 1;
	data->camera.invert_movement = 1;
	data->graphics.camera = &data->camera;
	data->graphics.map = data->map;
	data->graphics.window.width = data->graphics.window.width;
	data->graphics.window.height = data->graphics.window.height;
	data->graphics.z_buffer = malloc(sizeof(float) * data->graphics.window.width * data->graphics.window.height);
	data->graphics.use_depth_culling = 0;
	data->graphics.fill_triangles = 1;
	ctx.camera = &data->camera;
	ctx.map = data->map;
	ctx.window = data->graphics.window;
	adjust_camera_to_map(&ctx);
}
