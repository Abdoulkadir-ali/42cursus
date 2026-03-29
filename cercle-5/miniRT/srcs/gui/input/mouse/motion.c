/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:08:09 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:08:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	handle_mouse_rotation(t_gui *gui, int dx, int dy)
{
	gui->cam_ctrl.target_rot.yaw -= -dx * MOUSE_SENSITIVITY;
	gui->cam_ctrl.target_rot.pitch -= dy * MOUSE_SENSITIVITY;
	if (gui->cam_ctrl.target_rot.pitch > M_PI / 2 - 0.05)
		gui->cam_ctrl.target_rot.pitch = M_PI / 2 - 0.05;
	if (gui->cam_ctrl.target_rot.pitch < -M_PI / 2 + 0.05)
		gui->cam_ctrl.target_rot.pitch = -M_PI / 2 + 0.05;
	gui->render.dirty = true;
}

static void	handle_mouse_zoom_drag(t_gui *gui, int dy)
{
	gui->cam_ctrl.target_fov -= dy * 0.1;
	clamp_fov(&gui->cam_ctrl.target_fov);
	gui->render.dirty = true;
}

static void	update_inline_drag(t_gui *gui, int mouse_x)
{
	double	frac;
	double	val;
	int		rx;

	if (!gui->slider_state->dragging)
		return ;
	rx = mouse_x - gui->slider_state->track_x;
	if (rx < 0)
		rx = 0;
	if (rx > gui->slider_state->track_w)
		rx = gui->slider_state->track_w;
	frac = (double)rx / (double)gui->slider_state->track_w;
	val = gui->slider_state->dmin + frac
		* (gui->slider_state->dmax - gui->slider_state->dmin);
	if (gui->slider_state->prop)
	{
		pthread_rwlock_wrlock(&gui->scene_lock);
		gui->slider_state->prop->set(gui->scene,
			gui->slider_state->obj_index, val);
		pthread_rwlock_unlock(&gui->scene_lock);
	}
	if (gui->slider_state->on_change)
		gui->slider_state->on_change(gui);
	gui->render.dirty = true;
}

int	mouse_motion(int x, int y, t_gui *gui)
{
	t_vec2i	mouse;
	t_vec2i	delta;

	if (!gui)
		return (0);
	mouse = vec2i(x, y);
	gui->input.mouse.x = mouse.x;
	gui->input.mouse.y = mouse.y;
	if (gui->slider_state->dragging)
	{
		update_inline_drag(gui, mouse.x);
		gui->cam_ctrl.last_mouse = mouse;
		return (0);
	}
	delta = vec2i_sub(mouse, gui->cam_ctrl.last_mouse);
	if (gui->cam_ctrl.mouse_left_pressed)
		handle_mouse_rotation(gui, delta.x, delta.y);
	else if (gui->cam_ctrl.mouse_middle_pressed)
		handle_mouse_zoom_drag(gui, delta.y);
	gui->cam_ctrl.last_mouse = mouse;
	return (0);
}
