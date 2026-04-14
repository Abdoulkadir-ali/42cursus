/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "editor.h"
#include "camera.h"

static void	draft_update(t_gui *gui)
{
	const bool			was = gui->rt_engine.settings.draft_mode;
	t_camera_controller	*c;
	bool				mov;

	c = &gui->cam_ctrl;
	mov = (c->moving_forward || c->moving_backward || c->moving_left
			|| c->moving_right || c->moving_up || c->moving_down
			|| c->zooming_in || c->zooming_out || c->mouse_left_pressed
			|| c->mouse_middle_pressed);
	if (mov)
	{
		gui->rt_engine.settings.draft_mode = true;
		if (!gui->render.force_fullres)
			gui->render.scale = DRAFT_SCALE;
	}
	else
		gui->rt_engine.settings.draft_mode = false;
	if (was && !gui->rt_engine.settings.draft_mode && gui->opts.auto_fullres)
	{
		gui->opts.prev_valid = false;
		gui->render.scale = 1;
	}
}

void	scene_swap_step(t_gui *gui)
{
	if (!gui->render.scene_swap_pending)
		return ;
	if (gui->render.bake_job)
		bake_job_cancel(gui);
	gui->scene = gui->render.next_scene;
	gui->map_info.current = gui->render.next_entry;
	scene_snap_take(&gui->render.next_entry->snap, gui);
	gui->cam_ctrl.camera = &gui->scene->camera;
	gui->phys_engine.scene = gui->scene;
	gui->opts.prev_valid = false;
	reset_camera_view(gui);
	clear_selection(gui);
	anim_engine_rebuild_index(&gui->anim_engine, gui->scene);
	gui->render.next_scene = NULL;
	gui->render.next_entry = NULL;
	gui->render.scene_swap_pending = 0;
}

void	bvh_step(t_gui *gui)
{
	if (!gui->render.bvh_needs_rebuild)
		return ;
	rebuild_bvh(gui);
	gui->render.bvh_needs_rebuild = 0;
}

static void	raytrace_post(t_gui *gui, long long t0)
{
	const double	e = (now_ms() - t0) / 1000.0;

	if (e > 0)
		gui->render.render_fps = 0.9 * gui->render.render_fps + 0.1 * (1.0 / e);
	mlx_put_image_to_window(gui->win.mlx, gui->win.win,
		gui->win.disp_imgs[gui->render.back_idx], 0, 0);
	draw_ui_strings(gui, &gui->cam_ctrl);
	bake_job_poll(gui);
}

void	raytrace_step(t_gui *gui, double delta)
{
	long long	t0;

	if (!gui->scene)
		return ;
	draft_update(gui);
	if (gui->opts.adaptive_scale && !gui->rt_engine.settings.draft_mode)
		adaptive_scale(gui);
	t0 = now_ms();
	gui_render(gui);
	if (gui->opts.temporal_blend)
		blend_temporal(gui, delta);
	optimize_frames(gui, delta);
	save_depth(gui);
	if (!gui->rt_engine.settings.draft_mode)
		save_frame(gui);
	upscale_image(gui);
	if (gui->rt_engine.settings.bloom_enabled)
		bloom_frame(gui);
	draw_ui_pixels(gui);
	raytrace_post(gui, t0);
}
