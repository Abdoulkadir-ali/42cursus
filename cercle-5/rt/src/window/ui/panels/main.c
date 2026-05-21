/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:54:47 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 18:12:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"
#include "skeletal.h"

void	panel_sidebar(t_app *app);
void	panel_object_right(t_app *app);
void	panel_main_settings(t_app *app);
void	panel_main_animation(t_app *app);

static int	selected_animation_group(const t_app *app)
{
	const t_animator	*A;

	if (app->selected < 0 || app->selected >= (int)app->scene.n_bvh)
		return (0);
	if (!app->scene.animator)
		return (0);
	A = (const t_animator *)app->scene.animator;
	if (A->group_id <= 0)
		return (0);
	return (app->scene.bvh_objs[app->selected].group_id == A->group_id);
}

void	ui_draw_all(t_app *app)
{
	char	stats[64];
	int		mx;

	ui_begin(app);
	snprintf(stats, sizeof(stats), "FPS: %.1f (%.2fms)", app->time.fps, app->time.frame_dt * 1000.0);
	gfx_text(app, UI_PAD, app->img.h - UI_LINE_H - UI_PAD, stats, app->ui.theme.text);
	panel_sidebar(app);
	if (app->selected != 0x7fffffff)
		panel_object_right(app);
	if (selected_animation_group(app))
	{
		if (!app->ui.show_animation)
		{
			app->ui.show_animation = 1;
			g_layout.animation_x = app->img.w / 2 - UI_PANEL_W / 2;
			g_layout.animation_y = UI_PAD * 5;
		}
	}
	else
		app->ui.show_animation = 0;
	if (ui_button_at(app, (t_vec2i){app->img.w - 90, UI_PAD / 2}, (t_vec2i){80, 22}, "Settings"))
	{
		app->ui.show_settings = !app->ui.show_settings;
		if (app->ui.show_settings)
		{
			g_layout.settings_x = app->img.w / 2 - UI_PANEL_W / 2;
			g_layout.settings_y = UI_PAD * 5;
		}
	}
	if (app->ui.show_settings)
		panel_main_settings(app);
	if (app->ui.show_animation)
		panel_main_animation(app);
	mx = app->input.mouse_x;
	if (app->input.mouse_left && !app->ui.mouse_left_prev
		&& !app->ui.consume_input && !app->ui.tab_clicked
		&& mx >= UI_SIDEBAR_W + UI_PAD * 2
		&& mx <= app->img.w - UI_SIDEBAR_W - UI_PAD * 2)
		app->selected = 0x7fffffff;
	app->ui.tab_clicked = 0;
	ui_end(app);
}
