/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:54:58 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 18:13:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"
#include "skeletal.h"

static void	add_blackhole_at_cam(t_app *app)
{
	t_blackhole	*bh;
	t_blackhole	*tmp;
	int		cap;

	if (app->scene.n_bhs + 1 > app->scene.cap_bhs)
	{
		cap = app->scene.cap_bhs ? app->scene.cap_bhs * 2 : 4;
		tmp = (t_blackhole *)realloc(app->scene.bhs, sizeof(t_blackhole) * cap);
		if (!tmp)
			return ;
		app->scene.bhs = tmp;
		app->scene.cap_bhs = cap;
	}
	bh = &app->scene.bhs[app->scene.n_bhs++];
	bh->pos = v3_add(app->scene.cam.pos, v3_mul(app->scene.cam.dir, 12.0f));
	bh->rs = 0.6f;
	bh->lens_strength = 1.0f;
	bh->grav_strength = 1.0f;
	app->dirty = 1;
}

void	panel_main_settings(t_app *app)
{
	char	buf[64];
	int		*px = &g_layout.settings_x;
	int		*py = &g_layout.settings_y;

	if (*px < 0)
	{
		*px = app->img.w / 2 - UI_PANEL_W / 2;
		*py = UI_PAD * 5;
	}
	ui_panel_begin_p(app, px, py, &g_layout.settings_h, UI_PANEL_W, "Settings");
	{
		int	tw;

		tw = (UI_PANEL_W - UI_PAD * 2 - 8) / 5;
		if (ui_tab(app, "General", app->ui.settings_tab == 0, tw))
			app->ui.settings_tab = 0;
		if (ui_tab(app, "RT", app->ui.settings_tab == 1, tw))
			app->ui.settings_tab = 1;
		if (ui_tab(app, "Physics", app->ui.settings_tab == 2, tw))
			app->ui.settings_tab = 2;
		if (ui_tab(app, "Controls", app->ui.settings_tab == 3, tw))
			app->ui.settings_tab = 3;
		if (ui_tab(app, "Visual", app->ui.settings_tab == 4, tw))
			app->ui.settings_tab = 4;
		app->ui.cursor_y += UI_LINE_H + 6 + UI_PAD;
		app->ui.cursor_x = *px + UI_PAD;
	}
	if (app->ui.settings_tab == 0)
	{
		snprintf(buf, sizeof(buf), "%.1f", app->time.fps);
		ui_label_value(app, "FPS", buf);
		snprintf(buf, sizeof(buf), "%.1f ms", app->time.last_render_ms);
		ui_label_value(app, "frame", buf);
		ui_section(app, "-- Theme --");
		if (ui_button(app, "Dark Theme")) { ui_set_theme(app, 0); layout_save(); }
		if (ui_button(app, "Light Theme")) { ui_set_theme(app, 1); layout_save(); }
		if (ui_button(app, "Neon Theme")) { ui_set_theme(app, 2); layout_save(); }
		if (ui_button(app, "Tron Theme")) { ui_set_theme(app, 3); layout_save(); }
		ui_section(app, "-- Custom --");
		ui_color_swatch_hex(app, "bg color", &app->ui.theme.bg);
		ui_color_swatch_hex(app, "text color", &app->ui.theme.text);
		ui_section(app, "-- Performance --");
		if (ui_checkbox_b(app, "downscale on move", &app->set.render.downscale_on_move))
			app->dirty = 1;
		if (ui_slider_i(app, "downscale", &app->set.render.downscale, 1, 8))
			app->dirty = 1;
		if (ui_checkbox_b(app, "progressive", &app->set.render.progressive))
			app->dirty = 1;
		if (ui_slider_i(app, "accum cap", &app->set.render.accum_cap, 1, 1024))
			app->dirty = 1;
	}
	else if (app->ui.settings_tab == 1)
	{
		ui_section(app, "-- Raytracing --");
		if (ui_slider_i(app, "max bounces", &app->set.rt.max_bounces, 0, MAX_BOUNCES))
			app->dirty = 1;
		if (ui_checkbox_b(app, "shadows", &app->set.rt.shadows))
			app->dirty = 1;
		if (ui_checkbox_b(app, "soft shadows", &app->set.rt.soft_shadows))
			app->dirty = 1;
		if (ui_slider_i(app, "shadow samples", &app->set.rt.shadow_samples, 1, 16))
			app->dirty = 1;
		if (ui_checkbox_b(app, "indirect light", &app->set.rt.indirect_light))
			app->dirty = 1;
		if (ui_checkbox_b(app, "emitters as lights", &app->set.rt.emitters_as_lights))
			app->dirty = 1;
		if (ui_slider_f(app, "emit mult", &app->set.rt.emit_mult, 0.0f, 10.0f))
			app->dirty = 1;
		if (ui_checkbox_b(app, "show normals", &app->set.rt.show_normals))
			app->dirty = 1;
		if (ui_checkbox_b(app, "blackbody", &app->set.rt.blackbody))
			app->dirty = 1;
		if (ui_checkbox_b(app, "lensing on", &app->set.rt.lensing_on))
			app->dirty = 1;
		if (ui_checkbox_b(app, "collision heat", &app->set.rt.collision_heat))
			app->dirty = 1;
	}
	else if (app->ui.settings_tab == 2)
	{
		ui_section(app, "-- Physics --");
		if (ui_checkbox_b(app, "physics on", &app->set.physics.physics_on))
			app->dirty = 1;
		if (ui_checkbox(app, "paused", &app->phys.paused))
			app->dirty = 1;
		ui_slider_f(app, "time scale", &app->phys.time_scale, 0.0f, 4.0f);
		ui_slider_f(app, "gravity y", &app->scene.gravity.y, -50.0f, 50.0f);
		ui_slider_f(app, "friction", &app->set.physics.friction, 0.0f, 1.0f);
		if (ui_slider_f(app, "substeps", &app->set.physics.phys_substeps, 1.0f, 8.0f))
			app->dirty = 1;
		snprintf(buf, sizeof(buf), "%d", app->phys.n);
		ui_label_value(app, "bodies", buf);
		ui_section(app, "-- Black Holes --");
		if (ui_button(app, "+ Black hole"))
			add_blackhole_at_cam(app);
		if (app->scene.n_bhs > 0)
		{
			int	i;

			i = app->scene.n_bhs - 1;
			if (ui_slider_f(app, "last BH rs", &app->scene.bhs[i].rs, 0.05f, 50.0f))
				app->dirty = 1;
			if (ui_button(app, "Remove last BH"))
			{
				app->scene.n_bhs--;
				app->dirty = 1;
			}
			if (ui_select_row(app, buf, app->selected == i))
				app->selected = i;
		}
	}
	else if (app->ui.settings_tab == 3)
	{
		ui_section(app, "-- Camera --");
		ui_slider_f(app, "move speed", &app->set.controls.move_speed, 1.0f, 50.0f);
		ui_slider_f(app, "mouse sens", &app->set.controls.mouse_sens, 0.001f, 0.02f);
		if (ui_button(app, "Re-center camera"))
		{
			app->scene.cam.pos = v3(0, 0, 0);
			app->dirty = 1;
		}
		ui_section(app, "-- Animation --");
		if (ui_checkbox_b(app, "skinning", &app->set.anim.anim_skinning))
			app->dirty = 1;
		if (ui_checkbox_b(app, "use mips", &app->set.anim.use_mips))
			app->dirty = 1;
		if (ui_slider_f(app, "mip bias", &app->set.anim.mip_bias, -2.0f, 2.0f))
			app->dirty = 1;
	}
	else if (app->ui.settings_tab == 4)
	{
		ui_section(app, "-- Presets --");
		if (ui_button(app, "Neutral"))
		{
			app->set.render.exposure = 1.0f;
			app->set.render.brightness = 0.0f;
			app->set.render.contrast = 1.0f;
			app->set.render.saturation = 1.0f;
			app->set.render.gamma = 2.2f;
			app->set.render.vignette = 0.0f;
			app->dirty = 1;
		}
		if (ui_button(app, "Cinematic"))
		{
			app->set.render.exposure = 1.1f;
			app->set.render.brightness = -0.05f;
			app->set.render.contrast = 1.2f;
			app->set.render.saturation = 0.85f;
			app->set.render.gamma = 2.4f;
			app->set.render.vignette = 0.35f;
			app->dirty = 1;
		}
		if (ui_button(app, "Vivid"))
		{
			app->set.render.exposure = 1.2f;
			app->set.render.brightness = 0.05f;
			app->set.render.contrast = 1.15f;
			app->set.render.saturation = 1.5f;
			app->set.render.gamma = 2.0f;
			app->set.render.vignette = 0.1f;
			app->dirty = 1;
		}
		if (ui_button(app, "Flat / Raw"))
		{
			app->set.render.exposure = 1.0f;
			app->set.render.brightness = 0.0f;
			app->set.render.contrast = 0.85f;
			app->set.render.saturation = 0.9f;
			app->set.render.gamma = 1.8f;
			app->set.render.vignette = 0.0f;
			app->dirty = 1;
		}
		if (ui_button(app, "High Contrast"))
		{
			app->set.render.exposure = 1.0f;
			app->set.render.brightness = -0.1f;
			app->set.render.contrast = 1.5f;
			app->set.render.saturation = 1.2f;
			app->set.render.gamma = 2.2f;
			app->set.render.vignette = 0.25f;
			app->dirty = 1;
		}
		ui_section(app, "-- Camera --");
		if (ui_slider_f(app, "FOV", &app->scene.cam.fov, 20.0f, 180.0f))
			app->dirty = 1;
		ui_section(app, "-- Adjustments --");
		if (ui_slider_f(app, "exposure", &app->set.render.exposure, 0.1f, 5.0f))
			app->dirty = 1;
		if (ui_slider_f(app, "brightness", &app->set.render.brightness, -0.5f, 0.5f))
			app->dirty = 1;
		if (ui_slider_f(app, "contrast", &app->set.render.contrast, 0.5f, 2.0f))
			app->dirty = 1;
		if (ui_slider_f(app, "saturation", &app->set.render.saturation, 0.0f, 2.0f))
			app->dirty = 1;
		if (ui_slider_f(app, "gamma", &app->set.render.gamma, 1.0f, 3.0f))
			app->dirty = 1;
		if (ui_slider_f(app, "vignette", &app->set.render.vignette, 0.0f, 1.0f))
			app->dirty = 1;
	}
	ui_panel_end(app, &g_layout.settings_h);
}

void	panel_main_animation(t_app *app)
{
	char		buf[64];
	int		*px = &g_layout.animation_x;
	int		*py = &g_layout.animation_y;
	t_animator	*A = (t_animator *)app->scene.animator;

	if (*px < 0)
	{
		*px = app->img.w / 2 - UI_PANEL_W / 2;
		*py = UI_PAD * 5;
	}
	ui_panel_begin_p(app, px, py, &g_layout.animation_h, UI_PANEL_W, "Animation");
	if (!A || A->n_clips <= 0)
	{
		ui_label(app, "No animation attached.");
		if (A && A->n_clips == 0)
			ui_label(app, "No clips found in the current scene.");
		ui_panel_end(app, &g_layout.animation_h);
		return ;
	}

	ui_section(app, "Playback");
	if (ui_checkbox(app, "loop", &A->loop))
		app->dirty = 1;
	if (ui_button(app, A->playing ? "Pause" : "Play"))
		A->playing = !A->playing;
	if (ui_button(app, "Restart"))
	{
		A->time = 0.0f;
		int prev_play = A->playing;
		A->playing = 1;
		skel_animator_tick(app, 0.0f);
		A->playing = prev_play;
		app->dirty = 1;
	}
	if (ui_slider_f(app, "speed", &A->speed, 0.1f, 4.0f))
		app->dirty = 1;

	ui_section(app, "Clip");
	for (int i = 0; i < A->n_clips; i++)
	{
		const char *name = skel_animator_clip_name(A, i);
		if (ui_select_row(app, name, A->active == i))
		{
			A->active = i;
			A->time = 0.0f;
			int prev_play = A->playing;
			A->playing = 1;
			skel_animator_tick(app, 0.0f);
			A->playing = prev_play;
			app->dirty = 1;
		}
	}
	if (A->active >= 0 && A->active < A->n_clips)
	{
		float duration = skel_animator_clip_duration(A, A->active);
		if (duration <= 0.0f)
			duration = 1.0f;
		if (ui_slider_f(app, "position", &A->time, 0.0f, duration))
		{
			if (A->time < 0.0f)
				A->time = 0.0f;
			if (A->time > duration)
				A->time = duration;
			int prev_play = A->playing;
			A->playing = 1;
			skel_animator_tick(app, 0.0f);
			A->playing = prev_play;
			app->dirty = 1;
		}
		snprintf(buf, sizeof(buf), "%.2f / %.2f s", A->time, duration);
		ui_label_value(app, "time", buf);
	}
	ui_panel_end(app, &g_layout.animation_h);
}
