/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/04 02:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

int	mouse_click(int button, int x, int y, t_gui *gui)
{
	if (button == Button1)
	{ // Left button
		gui->mouse_left_pressed = true;
		gui->last_mouse_x = x;
		gui->last_mouse_y = y;
	}
	else if (button == Button2)
	{ // Middle button (MMB) pressed
		gui->mouse_middle_pressed = true;
		gui->last_mouse_x = x;
		gui->last_mouse_y = y;
	}
	else if (button == Button4)
	{ // Scroll up
		gui->target_fov -= ZOOM_SPEED;
		if (gui->target_fov < 10)
			gui->target_fov = 10;
		gui->dirty = true;
	}
	else if (button == Button5)
	{ // Scroll down
		gui->target_fov += ZOOM_SPEED;
		if (gui->target_fov > 170)
			gui->target_fov = 170;
		gui->dirty = true;
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_gui *gui)
{
	(void)x;
	(void)y;
	if (button == Button1)
		gui->mouse_left_pressed = false;
	else if (button == Button2)
		gui->mouse_middle_pressed = false;
	return (0);
}

int	mouse_motion(int x, int y, t_gui *gui)
{
	int dx = x - gui->last_mouse_x;
	int dy = y - gui->last_mouse_y;
	
	gui->mouse_x = x;
	gui->mouse_y = y;
	
	if (gui->mouse_left_pressed)
	{
		gui->target_rotation.yaw += -dx * MOUSE_SENSITIVITY;
		gui->target_rotation.pitch += dy * MOUSE_SENSITIVITY;
		if (gui->target_rotation.pitch > M_PI / 2 - 0.05)
			gui->target_rotation.pitch = M_PI / 2 - 0.05;
		if (gui->target_rotation.pitch < -M_PI / 2 + 0.05)
			gui->target_rotation.pitch = -M_PI / 2 + 0.05;
		gui->dirty = true;
	}
	else if (gui->mouse_middle_pressed)
	{
		gui->target_fov -= dy * 0.1; // Drag UP (dy < 0) -> Increase FOV
		if (gui->target_fov < 10) gui->target_fov = 10;
		if (gui->target_fov > 170) gui->target_fov = 170;
		gui->dirty = true;
	}
	gui->last_mouse_x = x;
	gui->last_mouse_y = y;
	return (0);
}