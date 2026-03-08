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

static long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

static double	update_delta(t_gui *gui)
{
	long long	current_time;
	double		delta;

	current_time = get_time_ms();
	if (gui->render.last_time > 0)
	{
		delta = (current_time - gui->render.last_time) / 1000.0;
		if (delta > 0)
			gui->render.fps = 0.9 * gui->render.fps + 0.1 * (1.0 / delta);
	}
	else
		delta = 0.016;
	gui->render.last_time = current_time;
	return (delta);
}

static void	update_animations(t_gui *gui, double delta)
{
	int		i;
	t_mesh	*mesh;

	if (!gui->scene || gui->scene->clip_count <= 0)
		return ;
	i = 0;
	while (i < gui->scene->mesh_count)
	{
		mesh = &gui->scene->meshes[i];
		if (mesh->skeleton)
		{
			glb_update_mesh_anim(mesh, gui->scene, delta);
			gui->render.dirty = true;
		}
		i++;
	}
}

static void	update_physics_step(t_gui *gui, double delta)
{
	double	fixed_dt;
	int		steps;

	if (!gui->scene || !gui->physics_enabled)
		return ;
	fixed_dt = (gui->phys_fixed_dt > 0.0) ? gui->phys_fixed_dt : (1.0 / 60.0);
	/* Clamp delta to prevent runaway accumulation after stalls */
	if (delta > fixed_dt * 3.0)
		delta = fixed_dt * 3.0;
	gui->phys_accumulator += delta;
	steps = 0;
	while (gui->phys_accumulator >= fixed_dt && steps < 3)
	{
		update_physics(gui->scene, fixed_dt);
		gui->phys_accumulator -= fixed_dt;
		steps++;
	}
	if (steps > 0)
		gui->render.dirty = true;
}

static void	update_autorefresh(t_gui *gui)
{
#if GUI_AUTOREFRESH_PHYSICS
	if (!gui->physics_enabled)
		return ;
	gui->render.dirty = true;
	if (gui->render.scale < GUI_AUTOREFRESH_SCALE)
		gui->render.scale = GUI_AUTOREFRESH_SCALE;
#else
	(void)gui;
#endif
}

static void	update_ambient(t_gui *gui)
{
	t_ambient	*amb;

	if (!gui->scene)
		return ;
	amb = &gui->scene->ambient;
	amb->rgb.x = ((gui->ambient_color >> 16) & 0xFF) / 255.0 * gui->ambient_intensity;
	amb->rgb.y = ((gui->ambient_color >> 8) & 0xFF) / 255.0 * gui->ambient_intensity;
	amb->rgb.z = (gui->ambient_color & 0xFF) / 255.0 * gui->ambient_intensity;
	amb->brightness = gui->ambient_intensity;
}

static void	render_if_dirty(t_gui *gui)
{
	if (!gui->render.dirty && !gui->render.last_dirty)
		return ;
	gui_render(gui);
	if (!gui->render.dirty)
		gui->render.last_dirty = false;
	else
		gui->render.last_dirty = true;
	gui->render.dirty = false;
}

static void	poll_map_job(t_gui *gui)
{
	t_map_job	*job;

	job = &gui->map_job;
	if (!job->active || !job->done)
		return ;
	pthread_join(job->tid, NULL);
	job->active = false;
	if (!job->entry || !job->entry->scene)
		return ;
	gui->map_info.current = job->entry;
	gui->scene = job->entry->scene;
	scene_snap_take(&job->entry->snap, gui);
	gui->cam_ctrl.camera = &gui->scene->camera;
	reset_camera_view(gui);
	clear_selection(gui);
	gui->render.dirty = true;
}

static int	render_loop(void *param)
{
	t_gui	*gui;
	double	delta;

	gui = (t_gui *)param;
	poll_map_job(gui);
	delta = update_delta(gui);
	update_animations(gui, delta);
	update_physics_step(gui, delta);
	update_autorefresh(gui);
	update_ambient(gui);
	gui_update_input(gui);
	render_if_dirty(gui);
	return (0);
}

/*
** Starts the main GUI loop.
*/
void	gui_loop(t_gui *gui)
{
	mlx_hook(gui->win.win, KeyPress, KeyPressMask, key_press, gui);
	mlx_hook(gui->win.win, KeyRelease, KeyReleaseMask, key_release, gui);
	mlx_hook(gui->win.win, ButtonPress, ButtonPressMask, mouse_click_hook(), gui);
	mlx_hook(gui->win.win, ButtonRelease, ButtonReleaseMask, mouse_release_hook(),
		gui);
	mlx_hook(gui->win.win, MotionNotify, PointerMotionMask, mouse_motion_hook(), gui);
	mlx_hook(gui->win.win, 17, 0, gui_window_close, gui);
	mlx_loop_hook(gui->win.mlx, (int (*)())render_loop, gui);
	mlx_loop(gui->win.mlx);
}
