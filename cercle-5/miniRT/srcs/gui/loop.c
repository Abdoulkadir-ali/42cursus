/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/04 02:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void update_input(t_gui *gui)
{
	bool	moved = false;

	if (!gui->camera) return;

	// Orientation Lerp/Snap
	if (fabs(gui->target_yaw - gui->yaw) > 0.0001 || fabs(gui->target_pitch - gui->pitch) > 0.0001)
	{
		gui->yaw += (gui->target_yaw - gui->yaw) * 0.3; // Responsive lerp
		gui->pitch += (gui->target_pitch - gui->pitch) * 0.3;
		moved = true;
	}

	double yaw = gui->yaw;
	
	// Forward on XZ plane for walking
	t_vec3 flat_fwd = vec3_norm(vec3(sin(yaw), 0, cos(yaw)));
	t_vec3 flat_right = vec3_norm(vec3(cos(yaw), 0, -sin(yaw)));
	t_vec3 world_up = vec3(0, 1, 0);

	double speed = gui->move_speed;

	if (gui->moving_forward)
	{
		gui->camera->pos = vec3_add(gui->camera->pos, vec3_scale(flat_fwd, -speed));
		moved = true;
	}
	if (gui->moving_backward)
	{
		gui->camera->pos = vec3_add(gui->camera->pos, vec3_scale(flat_fwd, speed));
		moved = true;
	}
	if (gui->moving_left)
	{
		gui->camera->pos = vec3_add(gui->camera->pos, vec3_scale(flat_right, -speed));
		moved = true;
	}
	if (gui->moving_right)
	{
		gui->camera->pos = vec3_add(gui->camera->pos, vec3_scale(flat_right, speed));
		moved = true;
	}
	if (gui->moving_up)
	{
		gui->camera->pos = vec3_add(gui->camera->pos, vec3_scale(world_up, speed));
		moved = true;
	}
	if (gui->moving_down)
	{
		gui->camera->pos = vec3_add(gui->camera->pos, vec3_scale(world_up, -speed));
		moved = true;
	}
	if (gui->zooming_in)
	{
		gui->camera->fov -= 1.0;
		if (gui->camera->fov < 10) gui->camera->fov = 10;
		moved = true;
	}
	if (gui->zooming_out)
	{
		gui->camera->fov += 1.0;
		if (gui->camera->fov > 170) gui->camera->fov = 170;
		moved = true;
	}

	if (moved)
		gui->dirty = true;
}

static int render_loop(void *param)
{
	t_gui *gui = (t_gui *)param;
	
	update_input(gui);
	
	if (gui->dirty)
	{
		gui_render(gui);
		gui->dirty = false;
	}
	return (0);
}

void gui_loop(t_gui *gui)
{
    mlx_hook(gui->win, KeyPress, KeyPressMask, key_press, gui);
    mlx_hook(gui->win, KeyRelease, KeyReleaseMask, key_release, gui);
    mlx_hook(gui->win, ButtonPress, ButtonPressMask, mouse_click, gui);
    mlx_hook(gui->win, ButtonRelease, ButtonReleaseMask, mouse_release, gui);
    mlx_hook(gui->win, MotionNotify, PointerMotionMask, mouse_motion, gui);
    mlx_loop_hook(gui->mlx, (int (*)())render_loop, gui);
    mlx_loop(gui->mlx);
}