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

#include "gui.h"
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

static int	mlx_mouse_motion(int x, int y, t_gui *gui)
{
	return (mouse_motion(vec2i(x, y), gui));
}

int (*mouse_motion_hook(void))(int, int, t_gui *)
{
	return (mlx_mouse_motion);
}

int	mouse_motion(t_vec2i mouse, t_gui *gui)
{
	t_vec2i	delta;

	if (!gui)
		return (0);
	gui->input.mouse_x = mouse.x;
	gui->input.mouse_y = mouse.y;
	if (gui->slider_state.dragging)
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
