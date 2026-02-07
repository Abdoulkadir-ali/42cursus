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
	if (button == 1)
	{ // Left button
		gui->mouse_left_pressed = true;
		gui->last_mouse_x = x;
		gui->last_mouse_y = y;
	}
	else if (button == 2)
	{ // Middle button (MMB) pressed - resets or prepares for FOV? 
	  // User said MMB to modify FOV, let's allow dragging or just use button
		gui->mouse_middle_pressed = true;
		gui->last_mouse_x = x;
		gui->last_mouse_y = y;
	}
	else if (button == 4)
	{ // Scroll up
		gui->camera->fov -= ZOOM_SPEED;
		if (gui->camera->fov < 10)
			gui->camera->fov = 10;
		gui->dirty = true;
	}
	else if (button == 5)
	{ // Scroll down
		gui->camera->fov += ZOOM_SPEED;
		if (gui->camera->fov > 170)
			gui->camera->fov = 170;
		gui->dirty = true;
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_gui *gui)
{
	(void)x;
	(void)y;
	if (button == 1)
		gui->mouse_left_pressed = false;
	else if (button == 2)
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
		gui->target_yaw += -dx * MOUSE_SENSITIVITY;
		gui->target_pitch += -dy * MOUSE_SENSITIVITY;
		if (gui->target_pitch > M_PI / 2 - 0.05)
			gui->target_pitch = M_PI / 2 - 0.05;
		if (gui->target_pitch < -M_PI / 2 + 0.05)
			gui->target_pitch = -M_PI / 2 + 0.05;
		gui->dirty = true;
	}
	else if (gui->mouse_middle_pressed)
	{
		gui->camera->fov += dy * 0.1;
		if (gui->camera->fov < 10) gui->camera->fov = 10;
		if (gui->camera->fov > 170) gui->camera->fov = 170;
		gui->dirty = true;
	}
	gui->last_mouse_x = x;
	gui->last_mouse_y = y;
	return (0);
}