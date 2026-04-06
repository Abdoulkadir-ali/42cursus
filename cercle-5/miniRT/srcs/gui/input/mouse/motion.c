/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 17:19:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "debug.h"

static void	handle_mouse_rotation(t_gui *gui, t_vec2i delta)
{
	if (delta.x == 0 && delta.y == 0)
		return ;
	ft_print_debug("ROTATION: sdx=%d sdy=%d\n", delta.x, delta.y);
	camera_rotate_yaw(gui, delta.x * MOUSE_SENSITIVITY);
	camera_rotate_pitch(gui, -delta.y * MOUSE_SENSITIVITY);
	gui->render.dirty = true;
}

static void	handle_mouse_zoom_drag(t_gui *gui, int dy)
{
	gui->cam_ctrl.target_fov -= dy * 0.1;
	clamp_fov(&gui->cam_ctrl.target_fov);
	gui->render.dirty = true;
}

static bool	handle_gui_motion(t_gui *gui, t_vec2i mouse)
{
	gui->input.mouse = mouse;
	widget_handle_motion(gui, mouse);
	if (gui->settings.dragging)
	{
		settings_handle_drag(gui, mouse);
		return (true);
	}
	if (gui->dragging_widget)
		return (true);
	if (gui->slider_state.dragging)
	{
		update_inline_drag(gui, mouse);
		gui->cam_ctrl.last_mouse = mouse;
		return (true);
	}
	return (false);
}

int	mouse_motion(t_vec2i mouse, t_gui *gui)
{
	t_vec2i	delta;

	if (!gui || handle_gui_motion(gui, mouse))
		return (0);
	delta = vec2i_sub(mouse, gui->cam_ctrl.last_mouse);
	if (gui->cam_ctrl.mouse_left_pressed || gui->cam_ctrl.mouse_middle_pressed)
	{
		if (delta.x != 0 || delta.y != 0)
			ft_print_debug("MOTION: m=%d,%d l=%d,%d d=%d,%d\n",
				mouse.x, mouse.y, gui->cam_ctrl.last_mouse.x,
				gui->cam_ctrl.last_mouse.y, delta.x, delta.y);
	}
	if (gui->cam_ctrl.mouse_left_pressed)
		handle_mouse_rotation(gui, delta);
	else if (gui->cam_ctrl.mouse_middle_pressed)
		handle_mouse_zoom_drag(gui, delta.y);
	gui->cam_ctrl.last_mouse = mouse;
	return (0);
}
