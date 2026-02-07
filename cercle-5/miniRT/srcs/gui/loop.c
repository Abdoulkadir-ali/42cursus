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
#include <sys/time.h>

static long long get_time_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

static void update_input(t_gui *gui)
{
	if (!gui->camera) return;

	double yaw = gui->yaw;
	t_vec3 flat_fwd = vec3_norm(vec3(sin(yaw), 0, cos(yaw)));
	t_vec3 flat_right = vec3_norm(vec3(cos(yaw), 0, -sin(yaw)));
	t_vec3 world_up = vec3(0, 1, 0);
	double speed = gui->move_speed;

	// 1. Update Target Position based on input
	if (gui->moving_forward)
		gui->target_position = vec3_add(gui->target_position, vec3_scale(flat_fwd, -speed));
	if (gui->moving_backward)
		gui->target_position = vec3_add(gui->target_position, vec3_scale(flat_fwd, speed));
	if (gui->moving_left)
		gui->target_position = vec3_add(gui->target_position, vec3_scale(flat_right, -speed));
	if (gui->moving_right)
		gui->target_position = vec3_add(gui->target_position, vec3_scale(flat_right, speed));
	if (gui->moving_up)
		gui->target_position = vec3_add(gui->target_position, vec3_scale(world_up, speed));
	if (gui->moving_down)
		gui->target_position = vec3_add(gui->target_position, vec3_scale(world_up, -speed));

	// 2. Smooth Orientation (Lerp)
	if (fabs(gui->target_yaw - gui->yaw) > 1e-4 || fabs(gui->target_pitch - gui->pitch) > 1e-4)
	{
		gui->yaw += (gui->target_yaw - gui->yaw) * 0.2;
		gui->pitch += (gui->target_pitch - gui->pitch) * 0.2;
		gui->dirty = true;
	}

	// 3. Smooth Position (Lerp)
	t_vec3 pos_diff = vec3_sub(gui->target_position, gui->camera->pos);
	if (vec3_mag_sq(pos_diff) > 1e-6)
	{
		gui->camera->pos = vec3_add(gui->camera->pos, vec3_scale(pos_diff, 0.2));
		gui->dirty = true;
	}

	// 4. Smooth FOV (Lerp)
	if (fabs(gui->target_fov - gui->camera->fov) > 1e-2)
	{
		gui->camera->fov += (gui->target_fov - gui->camera->fov) * 0.2;
		gui->dirty = true;
	}
	
	// Handle discrete input that sets dirty
	if (gui->zooming_in) { gui->target_fov -= 1.0; if (gui->target_fov < 10) gui->target_fov = 10; }
	if (gui->zooming_out) { gui->target_fov += 1.0; if (gui->target_fov > 170) gui->target_fov = 170; }
}

static int render_loop(void *param)
{
	t_gui *gui = (t_gui *)param;
	long long current_time = get_time_ms();
	
	if (gui->last_time > 0)
	{
		double delta = (current_time - gui->last_time) / 1000.0;
		if (delta > 0)
			gui->fps = 0.9 * gui->fps + 0.1 * (1.0 / delta); // Smooth FPS
	}
	gui->last_time = current_time;
	
	update_input(gui);
	
	// Raycast for hover info every frame (or only when mouse moved)
	// For responsiveness, let's just do it in update_input or here
	
	if (gui->dirty)
	{
		gui_render(gui);
		gui->dirty = false;
	}
	else
	{
		// Even if not "dirty" (scene change), we might want to update the overlay (FPS, Mouse info)
		// Option 1: Always redraw overlay at end of loop.
		// Option 2: Always render if overlay needs update.
		// Let's just draw the imagery to window again with new strings
		// But mlx_string_put doesn't redraw the background image.
		// To show real-time FPS, we need to redraw.
		// However, raytracing is slow. 
		// For now, let's only update when dirty.
		// Wait, if I want to show object hover info, I need to redraw.
		// Let's add a "force_overlay" concept or just use mlx_string_put on every loop.
		
		// If it's NOT dirty, we can't easily clear previous strings without redrawing image.
		// So let's just force a render if we want real-time overlay.
		// In a Raytracer, this is too expensive. 
		// I will only update the overlay info in gui_render.
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