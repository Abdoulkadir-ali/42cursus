/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:30:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void	handle_scroll(int button, t_gui *gui)
{
	if (button == Button4)
	{
		gui->cam_ctrl.target_fov -= ZOOM_SPEED;
		clamp_fov(&gui->cam_ctrl.target_fov);
		gui->render.dirty = true;
	}
	else if (button == Button5)
	{
		gui->cam_ctrl.target_fov += ZOOM_SPEED;
		clamp_fov(&gui->cam_ctrl.target_fov);
		gui->render.dirty = true;
	}
}

/*
** Handles mouse button press events.
*/
int	mouse_click(int button, int x, int y, t_gui *gui)
{
	if (button == Button1)
	{
		gui->cam_ctrl.mouse_left_pressed = true;
		gui->cam_ctrl.last_mouse_x = x;
		gui->cam_ctrl.last_mouse_y = y;
	}
	else if (button == Button2)
	{
		gui->cam_ctrl.mouse_middle_pressed = true;
		gui->cam_ctrl.last_mouse_x = x;
		gui->cam_ctrl.last_mouse_y = y;
	}
	else
		handle_scroll(button, gui);
	return (0);
}

/*
** Handles mouse button release events.
*/
int	mouse_release(int button, int x, int y, t_gui *gui)
{
	(void)x;
	(void)y;
	if (button == Button1)
		gui->cam_ctrl.mouse_left_pressed = false;
	else if (button == Button2)
		gui->cam_ctrl.mouse_middle_pressed = false;
	return (0);
}

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

/*
** Handles mouse motion events.
*/
int	mouse_motion(int x, int y, t_gui *gui)
{
	int	dx;
	int	dy;

	dx = x - gui->cam_ctrl.last_mouse_x;
	dy = y - gui->cam_ctrl.last_mouse_y;
	gui->input.mouse_x = x;
	gui->input.mouse_y = y;
	if (gui->cam_ctrl.mouse_left_pressed)
		handle_mouse_rotation(gui, dx, dy);
	else if (gui->cam_ctrl.mouse_middle_pressed)
		handle_mouse_zoom_drag(gui, dy);
	gui->cam_ctrl.last_mouse_x = x;
	gui->cam_ctrl.last_mouse_y = y;
	return (0);
}