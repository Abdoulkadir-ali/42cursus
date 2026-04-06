/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insp_row.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_insp_row_slider(t_gui *gui, t_vec2i pos, t_islider sl)
{
	t_vec2s	d;
	double	frac;
	int		fill_w;
	int		sl_w;

	d = gui->win.disp_size;
	sl_w = ui_sx(INSP_SL_W, d);
	frac = 0.0;
	if (sl.max > sl.min)
		frac = (*sl.ptr - sl.min) / (sl.max - sl.min);
	if (frac < 0.0)
		frac = 0.0;
	if (frac > 1.0)
		frac = 1.0;
	fill_w = (frac * sl_w);
	draw_slider_fill(gui, vec2i(pos.x + ui_sx(INSP_SL_OFF, d),
			pos.y + ui_sy(4, d)), fill_w, sl_w);
}

static void	draw_insp_row_input_cursor(t_gui *gui, t_vec2i pos, t_insp_edit *e)
{
	t_panel	cur;
	t_vec2s	d;
	int		cx;

	d = gui->win.disp_size;
	cx = pos.x + ui_sx(INSP_IN_OFF + 3, d) + (int)e->cursor * ui_sx(8, d);
	cur = (t_panel){.pos = vec2i(cx, pos.y + ui_sy(3, d)),
		.size = ui_size(1, INSP_ROW_H - 7, d),
		.bg = COL_ACCENT, .brd = COL_ACCENT};
	draw_panel(gui, cur);
}

static void	draw_insp_row_input(t_gui *gui, t_vec2i pos, t_islider sl)
{
	t_insp_edit	*e;
	t_vec2s		d;
	char		buf[24];
	t_panel		inp;
	int			bg;

	d = gui->win.disp_size;
	e = &gui->slider_state.insp_edit;
	bg = COL_INSP_INPUT_BG;
	if (e->active && e->value_ptr == sl.ptr)
		bg = COL_INSP_INPUT_ACTIVE_BG;
	inp = (t_panel){.pos = vec2i(pos.x + ui_sx(INSP_IN_OFF, d),
			pos.y + ui_sy(2, d)), .size = ui_size(INSP_IN_W,
			INSP_ROW_H - 4, d), .bg = bg, .brd = COL_BORDER};
	if (e->active && e->value_ptr == sl.ptr)
		inp.brd = COL_ACCENT;
	draw_panel(gui, inp);
	if (e->active && e->value_ptr == sl.ptr)
		snprintf(buf, sizeof(buf), "%s", e->buf);
	else
		snprintf(buf, sizeof(buf), "%.4g", *sl.ptr);
	gui_draw_string(gui, buf, vec2i(pos.x + ui_sx(INSP_IN_OFF + 3, d),
			pos.y + ui_sy(5, d)), COL_HOVER);
	if (e->active && e->value_ptr == sl.ptr)
		draw_insp_row_input_cursor(gui, pos, e);
}

void	draw_insp_row(t_gui *gui, t_vec2i pos, t_islider sl)
{
	t_vec2s	d;

	d = gui->win.disp_size;
	gui_draw_string(gui, sl.label, vec2i(pos.x, pos.y + ui_sy(4, d)), COL_TEXT);
	draw_insp_row_slider(gui, pos, sl);
	draw_insp_row_input(gui, pos, sl);
}

void	draw_insp_toggle_row(t_gui *gui, t_vec2i pos, const char *label,
		bool val)
{
	t_panel	btn;
	t_vec2s	d;
	int		bg_col;
	int		text_col;

	d = gui->win.disp_size;
	bg_col = COL_INSP_OFF_BG;
	text_col = COL_INSP_OFF_TEXT;
	if (val)
	{
		bg_col = COL_INSP_ON_BG;
		text_col = COL_INSP_ON_TEXT;
	}
	gui_draw_string(gui, label, vec2i(pos.x, pos.y + ui_sy(4, d)), COL_TEXT);
	btn = (t_panel){.pos = vec2i(pos.x + ui_sx(INSP_IN_OFF, d),
			pos.y + ui_sy(1, d)), .size = ui_size(INSP_IN_W, INSP_ROW_H - 2, d),
		.bg = bg_col, .brd = COL_BORDER};
	draw_panel(gui, btn);
	if (val)
		gui_draw_string(gui, " ON ", vec2i(pos.x + ui_sx(INSP_IN_OFF + 8, d),
				pos.y + ui_sy(5, d)), text_col);
	else
		gui_draw_string(gui, "OFF ", vec2i(pos.x + ui_sx(INSP_IN_OFF + 8, d),
				pos.y + ui_sy(5, d)), text_col);
}
