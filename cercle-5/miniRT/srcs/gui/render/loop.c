/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 16:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "physics.h"

/*
** Returns current time in milliseconds.
*/
static long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

/*
** Rendering loop callback function.
** Updates input, renders frame if needed, and calculates FPS.
*/
static int	render_loop(void *param)
{
	t_gui		*gui;
	long long	current_time;
	double		delta;

	gui = (t_gui *)param;
	current_time = get_time_ms();
	if (gui->render.last_time > 0)
	{
		delta = (current_time - gui->render.last_time) / 1000.0;
		if (delta > 0)
			gui->render.fps = 0.9 * gui->render.fps + 0.1 * (1.0 / delta);
	}
	else
		delta = 0.016; // default to ~60 FPS
	gui->render.last_time = current_time;

	// --- ANIMATION UPDATE ---
	if (gui->scene && gui->scene->clip_count > 0)
	{
		for (int i = 0; i < gui->scene->mesh_count; i++)
		{
			t_mesh *mesh = &gui->scene->meshes[i];
			if (mesh->skeleton)
			{
				glb_update_mesh_anim(mesh, gui->scene, delta);
				gui->render.dirty = true;
			}
		}
	}


	// --- PHYSICS UPDATE (fixed-timestep accumulator) ---
	if (gui->scene && gui->physics_enabled)
	{
		double fixed_dt = (gui->phys_fixed_dt > 0.0) ? gui->phys_fixed_dt : (1.0 / 60.0);
		gui->phys_accumulator += delta;
		int steps = 0;
		while (gui->phys_accumulator >= fixed_dt && steps < gui->phys_max_steps)
		{
			update_physics(gui->scene, fixed_dt);
			gui->phys_accumulator -= fixed_dt;
			steps++;
		}
		if (steps > 0)
		{
			/* Rebuild top-level BVH (TLAS) to reflect transformed objects. */
			if (gui->scene->bvh)
				bvh_destroy(gui->scene->bvh);
			gui->scene->bvh = bvh_create(gui->scene);
			gui->render.dirty = true;
		}
	}

	/* Auto-refresh & downscale when physics is running if enabled by define */
#if GUI_AUTOREFRESH_PHYSICS
	if (gui->physics_enabled)
	{
		gui->render.dirty = true;
		/* use a downscale to speed up continuous renders */
		if (gui->render.scale < GUI_AUTOREFRESH_SCALE)
			gui->render.scale = GUI_AUTOREFRESH_SCALE;
	}
#endif

	// --- AMBIENT LIGHT UPDATE ---
	if (gui->scene) {
		t_ambient *amb = &gui->scene->ambient;
		amb->rgb.x = ((gui->ambient_color >> 16) & 0xFF) / 255.0 * gui->ambient_intensity;
		amb->rgb.y = ((gui->ambient_color >> 8) & 0xFF) / 255.0 * gui->ambient_intensity;
		amb->rgb.z = (gui->ambient_color & 0xFF) / 255.0 * gui->ambient_intensity;
		amb->brightness = gui->ambient_intensity;
	}

	gui_update_input(gui);
	if (gui->render.dirty || gui->render.last_dirty)
	{
		gui_render(gui);
		if (!gui->render.dirty)
			gui->render.last_dirty = false;
		else
			gui->render.last_dirty = true;
		gui->render.dirty = false;
	}
	return (0);
}

/*
** Starts the main GUI loop.
*/
void	gui_loop(t_gui *gui)
{
	mlx_hook(gui->win.win, KeyPress, KeyPressMask, key_press, gui);
	mlx_hook(gui->win.win, KeyRelease, KeyReleaseMask, key_release, gui);
	mlx_hook(gui->win.win, ButtonPress, ButtonPressMask, mouse_click, gui);
	mlx_hook(gui->win.win, ButtonRelease, ButtonReleaseMask, mouse_release,
		gui);
	mlx_hook(gui->win.win, MotionNotify, PointerMotionMask, mouse_motion, gui);
	mlx_hook(gui->win.win, 17, 0, gui_window_close, gui);
	mlx_loop_hook(gui->win.mlx, (int (*)())render_loop, gui);
	mlx_loop(gui->win.mlx);
}
