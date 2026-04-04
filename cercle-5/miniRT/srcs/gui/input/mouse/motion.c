/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 23:35:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "debug.h"

static void	handle_mouse_rotation(t_gui *gui, t_vec2i delta)
{
	ssize_t	sdx;
	ssize_t	sdy;

	sdx = (ssize_t)delta.x;
	sdy = (ssize_t)delta.y;
	if (sdx == 0 && sdy == 0)
		return ;
	ft_print_debug("ROTATION: sdx=%zd sdy=%zd\n", sdx, sdy);
	camera_rotate_yaw(gui, (double)sdx * MOUSE_SENSITIVITY);
	camera_rotate_pitch(gui, (double)-sdy * MOUSE_SENSITIVITY);
	gui->render.dirty = true;
}

static void	handle_mouse_zoom_drag(t_gui *gui, ssize_t dy)
{
	gui->cam_ctrl.target_fov -= (double)dy * 0.1;
	clamp_fov(&gui->cam_ctrl.target_fov);
	gui->render.dirty = true;
}

static int	mlx_mouse_motion(int x, int y, void *param)
{
	t_gui	*gui;

	gui = (t_gui *)param;
	return (mouse_motion(vec2i(x, y), gui));
}

int	(*mouse_motion_hook(void))(int x, int y, void *param)
{
	return (mlx_mouse_motion);
}

int	mouse_motion(t_vec2i mouse, t_gui *gui)
{
	t_vec2i	delta;

	if (!gui)
		return (0);
	gui->input.mouse = mouse;
	if (gui->slider_state.dragging)
	{
		update_inline_drag(gui, mouse);
		gui->cam_ctrl.last_mouse = mouse;
		return (0);
	}
	delta = vec2i_sub(mouse, gui->cam_ctrl.last_mouse);
	if (gui->cam_ctrl.mouse_left_pressed || gui->cam_ctrl.mouse_middle_pressed)
	{
		if (delta.x != 0 || delta.y != 0)
		{
			ft_print_debug("MOTION: mouse=%zu,%zu last=%zu,%zu delta=%zd,%zd\n",
				mouse.x, mouse.y, gui->cam_ctrl.last_mouse.x,
				gui->cam_ctrl.last_mouse.y, delta.x, delta.y);
		}
	}
	if (gui->cam_ctrl.mouse_left_pressed)
	{
		handle_mouse_rotation(gui, delta);
	}
	else if (gui->cam_ctrl.mouse_middle_pressed)
		handle_mouse_zoom_drag(gui, (ssize_t)delta.y);
	gui->cam_ctrl.last_mouse = mouse;
	return (0);
}
