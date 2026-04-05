/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 21:06:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
** Drains a pending display resize posted by gui_window_resize (main thread).
** Installs new triple-buffer images, hands old images back for destruction,
** and recomputes UI layout — all before any worker is dispatched this frame.
*/
static void	disp_resize_step(t_gui *gui)
{
	int	front;
	int	i;

	if (!gui->render.disp_resize_pending)
		return ;
	i = 0;
	while (i < 3)
	{
		gui->render.old_disp_imgs[i] = gui->win.disp_imgs[i];
		gui->win.disp_imgs[i] = gui->render.pending_disp_imgs[i];
		gui->win.disp_addrs[i] = gui->render.pending_disp_addrs[i];
		i++;
	}
	gui->win.disp_line_len = gui->render.pending_disp_line_len;
	gui->win.disp_bpp = gui->render.pending_disp_bpp;
	gui->win.disp_endian = gui->render.pending_disp_endian;
	gui->win.disp_size = gui->render.pending_disp_size;
	front = atomic_load(&gui->render.front_idx);
	gui->render.back_idx = (front + 1) % 3;
	gui_recompute_layout(gui);
	gui->render.dirty = true;
	gui->render.disp_resize_pending = 0;
	gui->render.disp_resize_done = 1;
}

/*
** Composites pixel-based UI (panels, orientation gizmo) into the back
** buffer while the render thread owns it exclusively — no race possible.
** String-based text stays on the main thread (mlx_string_put is X11-direct).
*/
static void	overlay_step(t_gui *gui)
{
	draw_ui_pixels(gui);
}

/*
** Drains a pending scene swap posted by poll_map_job (MLX thread).
** Called at the top of render_frame — guarantees the render thread
** is not mid-traversal when the scene pointer changes.
*/
void	scene_swap_step(t_gui *gui)
{
	if (!gui->render.scene_swap_pending)
		return ;
	gui->scene = gui->render.next_scene;
	gui->map_info.current = gui->render.next_entry;
	scene_snap_take(&gui->render.next_entry->snap, gui);
	gui->cam_ctrl.camera = &gui->scene->camera;
	reset_camera_view(gui);
	clear_selection(gui);
	anim_engine_rebuild_index(&gui->anim_engine, gui->scene);
	gui->render.next_scene = NULL;
	gui->render.next_entry = NULL;
	gui->render.scene_swap_pending = 0;
}

/*
** Checks if the scene BVH is stale (from physics or animation moving objects)
** and rebuilds it if needed.  Called every frame before raytracing.
*/
void	bvh_step(t_gui *gui)
{
	if (!gui->render.bvh_needs_rebuild)
		return ;
	rebuild_bvh(gui);
	gui->render.bvh_needs_rebuild = 0;
}

/*
** Snaps the camera state, fires the raytracer (threaded internally),
** upscales, runs temporal optimizations, composites overlay pixels,
** then triple-buffer flips so the GUI thread blits the new frame.
*/
void	raytrace_step(t_gui *gui, double delta)
{
	long long	t0;
	double		elapsed;
	int			old_front;

	if (!gui->scene)
		return ;
	disp_resize_step(gui);
	if (gui->render.opts.adaptive_scale)
		adaptive_scale(gui);
	gui->render.snap_transform = gui->scene->camera.transform;
	gui->render.snap_fov = gui->scene->camera.fov;
	gui->render.snap_scale = gui->render.scale;
	gui->render.snap_delta = delta;
	gui->render.abort_render = 0;
	t0 = now_ms();
	gui_render(gui);
	if (gui->render.abort_render)
		return ;
	upscale_image(gui);
	optimize_frames(gui, delta);
	overlay_step(gui);
	elapsed = (now_ms() - t0) / 1000.0;
	if (elapsed > 0)
		gui->render.render_fps = 0.9 * gui->render.render_fps
			+ 0.1 * (1.0 / elapsed);
	old_front = atomic_load(&gui->render.front_idx);
	__sync_synchronize();
	atomic_store(&gui->render.front_idx, gui->render.back_idx);
	atomic_store(&gui->render.blit_img,
		gui->win.disp_imgs[gui->render.back_idx]);
	gui->render.back_idx = old_front;
	if (gui->render.disp_resize_done)
	{
		__sync_synchronize();
		gui->render.disp_destroy_pending = 1;
		gui->render.disp_resize_done = 0;
	}
}
