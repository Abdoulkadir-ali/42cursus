/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:11 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:21:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "projection.h"
#include <stdio.h>

static void	handle_arrow_keys(int keycode, t_data *data)
{
	if (keycode == data->buttons.keyboard.up_arrow)
	{
		if (data->keys.ctrl_left || data->keys.ctrl_right)
			adjust_move_speed(data, 1);
		else
			data->keys.up = 1;
	}
	else if (keycode == data->buttons.keyboard.down_arrow)
	{
		if (data->keys.ctrl_left || data->keys.ctrl_right)
			adjust_move_speed(data, 0);
		else
			data->keys.down = 1;
	}
	else if (keycode == data->buttons.keyboard.left_arrow)
		data->keys.left = 1;
	else if (keycode == data->buttons.keyboard.right_arrow)
		data->keys.right = 1;
}

static void	handle_ctrl_keys(int keycode, t_data *data)
{
	if (keycode == data->buttons.keyboard.ctrl_left)
		data->keys.ctrl_left = 1;
	else if (keycode == data->buttons.keyboard.ctrl_right)
		data->keys.ctrl_right = 1;
	else if (keycode == data->buttons.keyboard.shift_left)
		data->keys.shift_left = 1;
	else if (keycode == data->buttons.keyboard.shift_right)
		data->keys.shift_right = 1;
}

static void	handle_optimization_keys(int keycode, t_data *data)
{
	if (keycode == data->buttons.keyboard.l)
		data->keys.l = 1;
	else if (keycode == data->buttons.keyboard.z)
		data->keys.z = 1;
	else if (keycode == data->buttons.keyboard.f)
		data->keys.f = 1;
	else if (keycode == data->buttons.keyboard.h)
		data->keys.h = 1;
	else if (keycode == data->buttons.keyboard.d)
		data->keys.d = 1;
	else if (keycode == data->buttons.keyboard.t)
		data->keys.t = 1;
}

static void	clamp_values(t_data *data)
{
	if (data->lod_level < MIN_LOD_LEVEL)
		data->lod_level = MIN_LOD_LEVEL;
	if (data->lod_level > MAX_LOD_LEVEL)
		data->lod_level = MAX_LOD_LEVEL;
	if (data->camera.z_scale < MIN_Z_SCALE)
		data->camera.z_scale = MIN_Z_SCALE;
	if (data->camera.frustum_margin < MIN_FRUSTUM_MARGIN)
		data->camera.frustum_margin = MIN_FRUSTUM_MARGIN;
	if (data->camera.frustum_margin > MAX_FRUSTUM_MARGIN)
		data->camera.frustum_margin = MAX_FRUSTUM_MARGIN;
	if (data->camera.dampening_threshold < MIN_DAMPENING_THRESHOLD)
		data->camera.dampening_threshold = MIN_DAMPENING_THRESHOLD;
	if (data->camera.dampening_threshold > MAX_DAMPENING_THRESHOLD)
		data->camera.dampening_threshold = MAX_DAMPENING_THRESHOLD;
	if (data->camera.spline_segments < MIN_SPLINE_SEGMENTS)
		data->camera.spline_segments = MIN_SPLINE_SEGMENTS;
	if (data->camera.spline_segments > MAX_SPLINE_SEGMENTS)
		data->camera.spline_segments = MAX_SPLINE_SEGMENTS;
	data->camera.z_scale = floor(data->camera.z_scale * 10.0) / 10.0;
}

static void	handle_combo_actions(int keycode, t_data *data)
{
	if (keycode == data->buttons.keyboard.plus)
	{
		if (data->keys.l)
			data->lod_level++;
		else if (data->keys.z)
			data->camera.z_scale += 0.1;
		else if (data->keys.f)
			data->camera.frustum_margin += 10;
		else if (data->keys.d)
			data->camera.dampening_threshold += 5;
		else if (data->keys.t)
			data->camera.spline_segments += 2;
		clamp_values(data);
		redraw(data);
	}
	else if (keycode == data->buttons.keyboard.minus)
	{
		if (data->keys.l)
			data->lod_level--;
		else if (data->keys.z)
			data->camera.z_scale -= 0.1;
		else if (data->keys.f)
			data->camera.frustum_margin -= 10;
		else if (data->keys.d)
			data->camera.dampening_threshold -= 5;
		else if (data->keys.t)
			data->camera.spline_segments -= 2;
		clamp_values(data);
		redraw(data);
	}
	else if (keycode == data->buttons.keyboard.zero)
	{
		if (data->keys.l)
			data->lod_level = DEFAULT_LOD_LEVEL;
		else if (data->keys.z)
			data->camera.z_scale = DEFAULT_Z_SCALE;
		else if (data->keys.f)
			data->camera.frustum_margin = DEFAULT_FRUSTUM_MARGIN;
		else if (data->keys.d)
			data->camera.dampening_threshold = DEFAULT_DAMPENING_THRESHOLD;
		else if (data->keys.t)
			data->camera.spline_segments = DEFAULT_SPLINE_SEGMENTS;
		redraw(data);
	}
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == data->buttons.keyboard.esc)
		return (cleanup_and_exit(data));
	if (keycode == data->buttons.keyboard.r)
		reset_view(data);
	else if (keycode == data->buttons.keyboard.p)
		cycle_projection(data);
	else if (keycode == data->buttons.keyboard.n)
		cycle_map(data);
	else if (keycode == data->buttons.keyboard.s)
		cycle_gui_style(data);
	else if (keycode == data->buttons.keyboard.a)
	{
		data->render_mode = (data->render_mode + 1) % RENDER_MODE_COUNT;
		redraw(data);
	}
	else if (keycode == data->buttons.keyboard.x)
	{
		data->camera.use_z_divisor = !data->camera.use_z_divisor;
		redraw(data);
	}
	else if (keycode == data->buttons.keyboard.i)
	{
		data->camera.invert_movement = !data->camera.invert_movement;
		redraw(data);
	}
	else if (keycode == data->buttons.keyboard.v)
	{
		data->use_depth_culling = !data->use_depth_culling;
		redraw(data);
	}
	else if (keycode == data->buttons.keyboard.ctrl_left
		|| keycode == data->buttons.keyboard.ctrl_right
		|| keycode == data->buttons.keyboard.shift_left
		|| keycode == data->buttons.keyboard.shift_right)
		handle_ctrl_keys(keycode, data);
	else if (keycode == data->buttons.keyboard.l
		|| keycode == data->buttons.keyboard.z
		|| keycode == data->buttons.keyboard.f
		|| keycode == data->buttons.keyboard.d
		|| keycode == data->buttons.keyboard.t)
		handle_optimization_keys(keycode, data);
	else if (keycode == data->buttons.keyboard.plus
		|| keycode == data->buttons.keyboard.minus
		|| keycode == data->buttons.keyboard.zero)
		handle_combo_actions(keycode, data);
	else
		handle_arrow_keys(keycode, data);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == data->buttons.keyboard.up_arrow)
		data->keys.up = 0;
	else if (keycode == data->buttons.keyboard.down_arrow)
		data->keys.down = 0;
	else if (keycode == data->buttons.keyboard.left_arrow)
		data->keys.left = 0;
	else if (keycode == data->buttons.keyboard.right_arrow)
		data->keys.right = 0;
	else if (keycode == data->buttons.keyboard.ctrl_left)
		data->keys.ctrl_left = 0;
	else if (keycode == data->buttons.keyboard.ctrl_right)
		data->keys.ctrl_right = 0;
	else if (keycode == data->buttons.keyboard.shift_left)
		data->keys.shift_left = 0;
	else if (keycode == data->buttons.keyboard.shift_right)
		data->keys.shift_right = 0;
	else if (keycode == data->buttons.keyboard.l)
		data->keys.l = 0;
	else if (keycode == data->buttons.keyboard.z)
		data->keys.z = 0;
	else if (keycode == data->buttons.keyboard.f)
		data->keys.f = 0;
	else if (keycode == data->buttons.keyboard.d)
		data->keys.d = 0;
	else if (keycode == data->buttons.keyboard.t)
		data->keys.t = 0;
	return (0);
}

int	loop_hook(t_data *data)
{
	int	needs_redraw;

	needs_redraw = 0;
	if (data->camera.scale != data->camera.target_scale)
		needs_redraw = 1;
	process_movement(data);
	if (needs_redraw)
		redraw(data);
	return (0);
}
