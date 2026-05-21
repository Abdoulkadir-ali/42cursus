/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 18:28:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"
#include <math.h>
#include <stdio.h>

static int	slider_track(t_app *app, t_vec2i *pos, t_vec2i *size)
{
	t_vec2i	mouse;
	t_vec2i	hit_pos;
	t_vec2i	hit_size;

	pos->x = app->ui.cursor_x;
	pos->y = app->ui.cursor_y + UI_LINE_H;
	size->x = app->ui.panel_w - UI_PAD * 2;
	size->y = 6;
	mouse = (t_vec2i){app->ui.mx, app->ui.my};
	hit_pos = (t_vec2i){pos->x, pos->y - 10};
	hit_size = (t_vec2i){size->x, 24};
	return (pt_in(mouse, hit_pos, hit_size));
}

int	ui_slider_f(t_app *app, const char *label, float *v, float lo, float hi)
{
	t_vec2i	pos;
	t_vec2i	size;
	int		id;
	int		hover;
	int		clicked;
	float	t;
	char	buf[32];

	id = app->ui.next_id++;
	hover = slider_track(app, &pos, &size);
	if (hover && app->ui.mouse_left && !app->ui.mouse_left_prev)
		app->ui.active_id = id;
	clicked = 0;
	if (app->ui.active_id == id && app->ui.mouse_left)
	{
		app->ui.widget.slider_active_id = id;
		t = (float)(app->ui.mx - pos.x) / (float)size.x;
		*v = lo + ft_clampf(t, 0, 1) * (hi - lo);
		clicked = 1;
	}
	else if (app->ui.active_id == id && !app->ui.mouse_left)
		app->ui.widget.slider_active_id = 0;
	else if (app->ui.widget.slider_active_id == id)
		app->ui.widget.slider_active_id = 0;
	snprintf(buf, sizeof(buf), "%.3f", *v);
	gfx_text(app, pos.x, app->ui.cursor_y, label, app->ui.theme.text_dim);
	gfx_text(app, pos.x + size.x - gfx_text_width(buf), app->ui.cursor_y,
		buf, app->ui.theme.text);
	gfx_fill_rect(app, pos.x, pos.y, size.x, size.y, app->ui.theme.bg2);
	t = (*v - lo) / (hi - lo);
	gfx_fill_rect(app, pos.x, pos.y, (int)(t * size.x), size.y,
		app->ui.theme.accent);
	app->ui.cursor_y += size.y + UI_LINE_H + 4;
	return (clicked);
}

int	ui_slider_i(t_app *app, const char *label, int *v, int lo, int hi)
{
	float	fv;

	fv = (float)*v;
	if (ui_slider_f(app, label, &fv, (float)lo, (float)hi))
	{
		*v = (int)(fv + 0.5f);
		return (1);
	}
	return (0);
}

int	ui_log_f(t_app *app, const char *label, float *v, float lo, float hi)
{
	float	llo;
	float	lhi;
	float	lv;

	llo = log10f(lo);
	lhi = log10f(hi);
	lv = log10f(*v);
	if (ui_slider_f(app, label, &lv, llo, lhi))
	{
		*v = powf(10.0f, lv);
		return (1);
	}
	return (0);
}
