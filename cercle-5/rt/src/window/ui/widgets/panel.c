/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 18:28:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

void	ui_panel_begin(t_app *app, int x, int y, int h, int w, const char *title)
{
	app->ui.cursor_x = x + UI_PAD;
	app->ui.cursor_y = y + UI_LINE_H + UI_PAD;
	app->ui.panel_x = x;
	app->ui.panel_y = y;
	app->ui.panel_w = w;
	if (h > 0)
		gfx_fill_rect(app, x, y + UI_LINE_H + 4, w, h - (UI_LINE_H + 4),
			app->ui.theme.bg);
	gfx_fill_rect(app, x, y, w, UI_LINE_H + 4, app->ui.theme.header);
	gfx_text(app, x + UI_PAD, y + 2, title, app->ui.theme.text);
}

void	ui_panel_begin_p(t_app *app, int *x, int *y, int *h, int w,
			const char *title)
{
	t_vec2i	mouse;
	t_vec2i	hdr_pos;
	t_vec2i	hdr_size;

	ui_panel_begin(app, *x, *y, *h, w, title);
	mouse = (t_vec2i){app->ui.mx, app->ui.my};
	hdr_pos = (t_vec2i){*x, *y};
	hdr_size = (t_vec2i){w, UI_LINE_H + 4};
	if (!app->ui.drag_active && pt_in(mouse, hdr_pos, hdr_size)
		&& app->ui.mouse_left && !app->ui.mouse_left_prev)
	{
		app->ui.drag_active = 1;
		app->ui.widget.drag_x = x;
		app->ui.widget.drag_y = y;
	}
	if (app->ui.drag_active && app->ui.widget.drag_x == x)
	{
		*x += app->input.mouse_dx;
		*y += app->input.mouse_dy;
		app->ui.consume_input = 1;
	}
}

void	ui_panel_end(t_app *app, int *h)
{
	t_vec2i	panel_pos;
	t_vec2i	panel_size;
	int		final_h;

	final_h = app->ui.cursor_y - app->ui.panel_y + UI_PAD / 2;
	if (h)
		*h = final_h;
	panel_pos = (t_vec2i){app->ui.panel_x, app->ui.panel_y};
	panel_size = (t_vec2i){app->ui.panel_w, final_h};
	gfx_rect_outline(app, panel_pos.x, panel_pos.y, panel_size.x, panel_size.y,
		app->ui.theme.border);
	app->ui.consume_input |= pt_in((t_vec2i){app->ui.mx, app->ui.my},
			panel_pos, panel_size);
}
