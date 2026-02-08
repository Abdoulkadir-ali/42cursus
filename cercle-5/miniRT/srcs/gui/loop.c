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

static long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

static void	update_input(t_gui *gui)
{
	t_vec3	forward;
	t_vec3	up;
	double	speed;
	t_vec3	pos_diff;

	if (!gui->camera)
		return ;
	// Calculate current 3D basis vectors based on CURRENT gui->rotation
	// (Matching gui_render's logic for consistency)
	forward = get_camera_forward(gui->rotation.pitch, gui->rotation.yaw);
	t_vec3 right = vec3_norm(vec3_cross(forward, vec3(0, 1, 0)));
		// Switch to Y-up
	if (vec3_mag_sq(right) < 1e-6)
		right = vec3(1, 0, 0);
	up = vec3_cross(right, forward);
	speed = gui->move_speed;
	// 1. Update Target Position based on input (Local movement)
	if (gui->moving_forward)
		gui->target_position = vec3_add(gui->target_position,
				vec3_scale(forward, speed));
	if (gui->moving_backward)
		gui->target_position = vec3_add(gui->target_position,
				vec3_scale(forward, -speed));
	if (gui->moving_left)
		gui->target_position = vec3_add(gui->target_position, vec3_scale(right,
					-speed));
	if (gui->moving_right)
		gui->target_position = vec3_add(gui->target_position, vec3_scale(right,
					speed));
	if (gui->moving_up)
		gui->target_position = vec3_add(gui->target_position, vec3_scale(up,
					speed));
	if (gui->moving_down)
		gui->target_position = vec3_add(gui->target_position, vec3_scale(up,
					-speed));
	// 2. Smooth Orientation (Lerp)
	if (fabs(gui->target_rotation.yaw - gui->rotation.yaw) > 1e-4
		|| fabs(gui->target_rotation.pitch - gui->rotation.pitch) > 1e-4)
	{
		gui->rotation.yaw += (gui->target_rotation.yaw - gui->rotation.yaw)
			* 0.2;
		gui->rotation.pitch += (gui->target_rotation.pitch
				- gui->rotation.pitch) * 0.2;
		gui->dirty = true;
	}
	// 3. Smooth Position (Lerp)
	pos_diff = vec3_sub(gui->target_position, gui->camera->transform.pos);
	if (vec3_mag_sq(pos_diff) > 1e-6)
	{
		gui->camera->transform.pos = vec3_add(gui->camera->transform.pos, vec3_scale(pos_diff,
					0.2));
		gui->dirty = true;
	}
	// 4. Smooth FOV (Lerp)
	if (fabs(gui->target_fov - gui->camera->fov) > 1e-2)
	{
		gui->camera->fov += (gui->target_fov - gui->camera->fov) * 0.2;
		gui->dirty = true;
	}
	// Dynamic Resolution: If anything is moving/interpolating, use low-res
	if (gui->dirty)
		gui->render_scale = 2; // 1/2 resolution (subtle)
	else
		gui->render_scale = 1; // Full resolution
	// Handle discrete input that sets dirty
	if (gui->zooming_in)
	{
		gui->target_fov -= 1.0;
		if (gui->target_fov < 10)
			gui->target_fov = 10;
	}
	if (gui->zooming_out)
	{
		gui->target_fov += 1.0;
		if (gui->target_fov > 170)
			gui->target_fov = 170;
	}
}

static int	render_loop(void *param)
{
	t_gui		*gui;
	long long	current_time;
	double		delta;
	static bool	last_dirty = false;

	gui = (t_gui *)param;
	current_time = get_time_ms();
	if (gui->last_time > 0)
	{
		delta = (current_time - gui->last_time) / 1000.0;
		if (delta > 0)
			gui->fps = 0.9 * gui->fps + 0.1 * (1.0 / delta); // Smooth FPS
	}
	gui->last_time = current_time;
	update_input(gui);
	// If was_dirty is true, we render in low-res during movement
	// But as soon as it BECOMES not dirty (stopped),
		we want one last FULL render.
	if (gui->dirty || last_dirty)
	{
		gui_render(gui);
		if (!gui->dirty)
			last_dirty = false; // Just finished the clean pass
		else
			last_dirty = true;
		gui->dirty = false;
	}
	return (0);
}

void	gui_loop(t_gui *gui)
{
	mlx_hook(gui->win, KeyPress, KeyPressMask, key_press, gui);
	mlx_hook(gui->win, KeyRelease, KeyReleaseMask, key_release, gui);
	mlx_hook(gui->win, ButtonPress, ButtonPressMask, mouse_click, gui);
	mlx_hook(gui->win, ButtonRelease, ButtonReleaseMask, mouse_release, gui);
	mlx_hook(gui->win, MotionNotify, PointerMotionMask, mouse_motion, gui);
	mlx_loop_hook(gui->mlx, (int (*)())render_loop, gui);
	mlx_loop(gui->mlx);
}