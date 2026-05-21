/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 17:11:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "core.h"
#include <stdatomic.h>
#include "skeletal.h"
#include <stdatomic.h>

static void	tick_time(t_app *app)
{
	double	now;
	double	dt;

	now = time_ms_now();
	if (app->time.last_t == 0.0)
		app->time.last_t = now;
	dt = (now - app->time.last_t) / 1000.0;
	app->time.last_t = now;
	app->time.frame_dt = dt;
	app->time.fps_acc += dt;
	app->time.frames++;
	if (app->time.fps_acc >= 0.4)
	{
		app->time.fps = app->time.frames / app->time.fps_acc;
		app->time.frames = 0;
		app->time.fps_acc = 0.0;
	}
}

static void	pre_render_downscale(t_app *app)
{
	int	d;

	d = 1;
	if (!app->set.render.downscale_on_move)
	{
		app->set.render.downscale = 1;
		return ;
	}
	if (app->moving)
		d = 2;
	if (app->moving && (app->scene.n_bvh > 50000 || app->set.rt.max_bounces > 1))
		d = 4;
	app->set.render.downscale = d;
}

int	on_loop(t_app *app)
{
	tick_time(app);
	poll_window_size(app);
	update_camera(app);
	if (app->set.physics.physics_on && app->phys.enabled && !app->phys.paused
		&& app->phys.n > 0)
	{
		int	steps;
		int	i;

		steps = (int)app->set.physics.phys_substeps;
		if (steps < 1)
			steps = 1;
		i = 0;
		while (i < steps)
		{
			phys_step(app, (float)app->time.frame_dt / steps);
			i++;
		}
	}
	pre_render_downscale(app);
	if (app->scene.animator)
	{
		t_animator *A = (t_animator *)app->scene.animator;
		if (A->playing)
			skel_animator_tick(app, (float)app->time.frame_dt);
	}
	if (app->dirty || app->moving)
	{
		app->accum_samples = 0;
		render_frame(app);
		app->dirty = 0;
	}
	else if (app->set.render.progressive && app->set.render.downscale <= 1
		&& app->accum_samples < app->set.render.accum_cap)
	{
		render_frame(app);
	}
	if (app->input.mouse_left_clicked && !app->ui.consume_input)
	{
		int pmx = app->input.mouse_x;
		int in_panels = (pmx < UI_SIDEBAR_W + UI_PAD * 2)
					 || (pmx > app->img.w - UI_SIDEBAR_W - UI_PAD * 2);
		if (!in_panels) {
			int id = pick_at(app, app->input.mouse_x, app->input.mouse_y);
			app->selected = id;
		}
	}
	if (app->input.mouse_middle_clicked && !app->ui.consume_input)
	{
	   int id;

	   id = pick_at(app, app->input.mouse_x, app->input.mouse_y);
	   if (id != 0x7fffffff && id >= 0)
	   {
		   t_vec3 c;
		   t_vec3 d;

		   c = object_center(&app->scene.bvh_objs[id]);
		   d = v3_sub(c, app->scene.cam.pos);
		   if (v3_dot(d, d) > 1e-8f)
		   {
			   d = v3_norm(d);
			   phys_apply_impulse(&app->phys, id, v3_mul(d, 8.0f));
			   app->phys.enabled = 1;
			   app->dirty = 1;
		   }
	   }
	}
	app->input.mouse_left_clicked = 0;
	app->input.mouse_right_clicked = 0;
	app->input.mouse_middle_clicked = 0;
	if (app->set.controls.show_gui)
		ui_draw_all(app);
	// Move mouse_left_prev update here for robust UI
	app->ui.mouse_left_prev = app->ui.mouse_left;
	if (app->set.render.selection_outline && app->selected != 0x7fffffff)
		gfx_outline_object(app, app->selected);
	/* Ensure we observe worker writes before displaying */
	atomic_thread_fence(memory_order_acquire);
	mlx_put_image_to_window(app->mlx, app->win, app->img.img, 0, 0);
	app->input.mouse_dx = 0;
	app->input.mouse_dy = 0;
	return (0);
}