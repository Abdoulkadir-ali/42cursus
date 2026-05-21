/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 18:28:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	ui_num_input(t_app *app, const char *label, float *v,
		unsigned int label_col, int bw)
{
	int				id;
	int				hover;
	int				changed;
	float			delta;
	float			f_norm;
	char			buf[64];
	t_vec2i			pos;
	t_vec2i			size;
	unsigned int	bg;

	id = app->ui.next_id++;
	pos = (t_vec2i){app->ui.cursor_x, app->ui.cursor_y};
	size = (t_vec2i){bw, UI_LINE_H + 8};
	hover = pt_in((t_vec2i){app->ui.mx, app->ui.my}, pos, size);
	changed = 0;
	if (hover && app->ui.mouse_left && !app->ui.mouse_left_prev)
	{
		app->ui.active_id = id;
		app->ui.widget.anchor_mx = app->ui.mx;
		app->ui.widget.start_v = *v;
		if (app->ui.kb_focus != id)
		{
			app->ui.kb_focus = id;
			snprintf(app->ui.input_buf, sizeof(app->ui.input_buf), "%.3f", *v);
		}
	}
	if (app->ui.active_id == id && app->ui.mouse_left)
	{
		delta = (float)(app->ui.mx - app->ui.widget.anchor_mx) * 0.1f;
		if (app->input.keys[65505])
			delta *= 10.0f;
		if (app->input.keys[65507])
			delta *= 0.1f;
		*v = app->ui.widget.start_v + delta;
		snprintf(app->ui.input_buf, sizeof(app->ui.input_buf), "%.3f", *v);
		changed = 1;
	}
	bg = app->ui.theme.bg2;
	if (app->ui.kb_focus == id)
		bg = app->ui.theme.btn_act;
	else if (hover)
		bg = app->ui.theme.btn_hov;
	gfx_fill_rect(app, pos.x, pos.y, size.x, size.y, bg);
	gfx_fill_rect(app, pos.x, pos.y, 16, size.y, label_col);
	gfx_text(app, pos.x + 5, pos.y + 5, label, app->ui.theme.text);
	f_norm = (*v > 100.0f) ? 1.0f
		: ((*v < -100.0f) ? 0.0f : (*v + 100.0f) / 200.0f);
	gfx_fill_rect(app, pos.x + 16, pos.y + size.y - 3,
		(int)(f_norm * (size.x - 16)), 3, label_col | 0x88000000);
	if (app->ui.kb_focus == id)
	{
		float val = atof(app->ui.input_buf);
		if (val != *v)
		{
			*v = val;
			changed = 1;
		}
		gfx_text(app, pos.x + 20, pos.y + 5, app->ui.input_buf,
			app->ui.theme.text);
	}
	else
	{
		snprintf(buf, sizeof(buf), "%.2f", *v);
		gfx_text(app, pos.x + 20, pos.y + 5, buf, app->ui.theme.text);
	}
	app->ui.cursor_x += size.x + 4;
	return (changed);
}

int	ui_vec3_edit(t_app *app, const char *label, t_vec3 *v)
{
	int		changed;
	int		old_x;
	int		label_w;
	int		bw;

	changed = 0;
	old_x = app->ui.cursor_x;
	label_w = 75;
	bw = (app->ui.panel_w - UI_PAD * 2 - label_w - 8) / 3;
	gfx_text(app, app->ui.cursor_x, app->ui.cursor_y + 5, label,
		app->ui.theme.text);
	app->ui.cursor_x += label_w;
	changed |= ui_num_input(app, "X", &v->x, UI_COL_X, bw);
	changed |= ui_num_input(app, "Y", &v->y, UI_COL_Y, bw);
	changed |= ui_num_input(app, "Z", &v->z, UI_COL_Z, bw);
	app->ui.cursor_x = old_x;
	app->ui.cursor_y += UI_LINE_H + 14;
	return (changed);
}

int	ui_handle_key(t_app *app, int key)
{
	int	len;

	if (!app->ui.kb_focus)
		return (0);
	len = strlen(app->ui.input_buf);
	if (key == 65293 || key == 65307)
	{
		app->ui.kb_focus = 0;
		return (1);
	}
	if (key == 65288 && len > 0)
		app->ui.input_buf[len - 1] = '\0';
	else if (len < 31)
	{
		if ((key >= '0' && key <= '9') || key == '.' || key == '-')
		{
			app->ui.input_buf[len] = (char)key;
			app->ui.input_buf[len + 1] = '\0';
		}
	}
	return (1);
}
