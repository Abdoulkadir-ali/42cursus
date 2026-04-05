/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 01:02:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "editor.h"

/*
** Composites pixel-based UI (panels, orientation gizmo) into the back buffer.
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

	if (!gui->scene)
		return ;
	if (gui->opts.adaptive_scale)
		adaptive_scale(gui);
	t0 = now_ms();
	gui_render(gui);
	save_frame(gui);
	if (gui->opts.temporal_blend)
		blend_temporal(gui, delta);
	upscale_image(gui);
	optimize_frames(gui, delta);
	overlay_step(gui);
	elapsed = (now_ms() - t0) / 1000.0;
	if (elapsed > 0)
		gui->render.render_fps = 0.9 * gui->render.render_fps
			+ 0.1 * (1.0 / elapsed);
	mlx_put_image_to_window(gui->win.mlx, gui->win.win,
		gui->win.disp_imgs[gui->render.back_idx], 0, 0);
	draw_ui_strings(gui, &gui->cam_ctrl);
	(void)elapsed;
}
