/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:58:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 18:28:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

void	ui_begin(t_app *app)
{
	if (!app->ui.widget.initialized)
	{
		ui_set_theme(app, g_layout.theme_preset >= 0 && g_layout.theme_preset <= 3
			? g_layout.theme_preset : 0);
		app->ui.widget.initialized = 1;
	}
	app->ui.next_id = 1;
	app->ui.hot_id = 0;
	app->ui.mx = app->input.mouse_x;
	app->ui.my = app->input.mouse_y;
	app->ui.mouse_left = app->input.mouse_left;
	if (app->ui.active_id != 0
		&& app->ui.active_id != app->ui.widget.slider_active_id)
		app->ui.consume_input = 1;
	else
		app->ui.consume_input = 0;
	if (app->ui.mouse_left && !app->ui.mouse_left_prev && !app->ui.consume_input)
		app->ui.kb_focus = 0;
}

void	ui_end(t_app *app)
{
	app->ui.mouse_left_prev = app->ui.mouse_left;
	if (!app->ui.mouse_left)
	{
		app->ui.active_id = 0;
		if (app->ui.drag_active)
		{
			app->ui.drag_active = 0;
			app->ui.widget.drag_x = NULL;
			app->ui.widget.drag_y = NULL;
		}
	}
	if (app->ui.active_id == 0)
		app->ui.consume_input = 0;
	app->input.mouse_wheel = 0;
}
