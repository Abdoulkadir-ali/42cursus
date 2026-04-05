/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insp_row.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 19:14:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_insp_header(t_gui *gui, t_vec2i pos, const char *title)
{
	t_vec2i	d;
	t_panel	sep;

	d = gui->win.disp_size;
	gui_draw_string(gui, title, pos, COL_ACCENT);
	sep = (t_panel){
		.pos = vec2i(pos.x, pos.y + ui_sy(INSP_HDR_STEP - 3, d)),
		.size = vec2i(ui_sx(INSP_IN_OFF + INSP_IN_W, d), 1),
		.bg = COL_BORDER, .brd = COL_BORDER};
	draw_panel(gui, sep);
}

void	draw_insp_color_swatch(t_gui *gui, t_vec2i pos, double r, double g,
		double b)
{
	t_panel	sw;
	t_vec2i	d;
	int		ir;
	int		ig;
	int		ib;

	d = gui->win.disp_size;	ir = (int)(r >= 1.5 ? r : r * 255.0);
	ig = (int)(g >= 1.5 ? g : g * 255.0);
	ib = (int)(b >= 1.5 ? b : b * 255.0);
	if (ir < 0)
		ir = 0;
	if (ir > 255)
		ir = 255;
	if (ig < 0)
		ig = 0;
	if (ig > 255)
		ig = 255;
	if (ib < 0)
		ib = 0;
	if (ib > 255)
		ib = 255;
	sw = (t_panel){
		.pos = pos, .size = ui_size(14, 14, d),
		.bg = (ir << 16) | (ig << 8) | ib,
		.brd = 0x666666};
	draw_panel(gui, sw);
}

static void	draw_insp_row_slider(t_gui *gui, t_vec2i pos, t_islider sl)
{
	t_vec2i	d;
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
	fill_w = (int)(frac * sl_w);
	draw_slider_fill(gui, vec2i(pos.x + ui_sx(INSP_SL_OFF, d), pos.y + ui_sy(4, d)),
		fill_w, sl_w);
}

static void	draw_insp_row_input(t_gui *gui, t_vec2i pos, t_islider sl)
{
	t_insp_edit	*e;
	t_vec2i		d;
	bool		editing;
	int			brd;
	char		buf[24];
	t_panel		inp;

	d = gui->win.disp_size;
	e = &gui->slider_state.insp_edit;
	editing = e->active && e->value_ptr == sl.ptr;
	brd = editing ? COL_ACCENT : COL_BORDER;
	inp = (t_panel){
		.pos = vec2i(pos.x + ui_sx(INSP_IN_OFF, d), pos.y + ui_sy(2, d)),
		.size = vec2i(ui_sx(INSP_IN_W, d), ui_sy(INSP_ROW_H - 4, d)),
		.bg = editing ? 0x0E0E1A : 0x141420,
		.brd = brd};
	draw_panel(gui, inp);
	if (editing)
		snprintf(buf, sizeof(buf), "%s", e->buf);
	else
		snprintf(buf, sizeof(buf), "%.4g", *sl.ptr);
	gui_draw_string(gui, buf,
		vec2i(pos.x + ui_sx(INSP_IN_OFF + 3, d), pos.y + ui_sy(5, d)), COL_HOVER);
	if (editing)
	{
		t_panel cur;
		int		cx;
		cx = pos.x + ui_sx(INSP_IN_OFF + 3, d) + e->cursor * ui_sx(8, d);
		cur = (t_panel){
			.pos = vec2i(cx, pos.y + ui_sy(3, d)),
			.size = vec2i(1, ui_sy(INSP_ROW_H - 7, d)),
			.bg = COL_ACCENT, .brd = COL_ACCENT};
		draw_panel(gui, cur);
	}
}

void	draw_insp_row(t_gui *gui, t_vec2i pos, t_islider sl)
{
	t_vec2i	d;

	d = gui->win.disp_size;
	gui_draw_string(gui, sl.label, vec2i(pos.x, pos.y + ui_sy(4, d)), COL_TEXT);
	draw_insp_row_slider(gui, pos, sl);
	draw_insp_row_input(gui, pos, sl);
}

void	draw_insp_toggle_row(t_gui *gui, t_vec2i pos, const char *label,
		bool val)
{
	t_panel	btn;
	t_vec2i	d;
	int		bg;
	int		col;

	d = gui->win.disp_size;
	bg = val ? 0x206040 : 0x402020;
	col = val ? 0x40FF80 : 0xFF5050;
	gui_draw_string(gui, label, vec2i(pos.x, pos.y + ui_sy(4, d)), COL_TEXT);
	btn = (t_panel){
		.pos = vec2i(pos.x + ui_sx(INSP_IN_OFF, d), pos.y + ui_sy(1, d)),
		.size = vec2i(ui_sx(INSP_IN_W, d), ui_sy(INSP_ROW_H - 2, d)),
		.bg = bg, .brd = COL_BORDER};
	draw_panel(gui, btn);
	gui_draw_string(gui, val ? " ON " : "OFF ",
		vec2i(pos.x + ui_sx(INSP_IN_OFF + 8, d), pos.y + ui_sy(5, d)), col);
}

void	draw_panel_insp_rows(t_gui *gui, t_islider *sl, int count, t_vec2i pos)
{
	t_vec2i	d;
	int		i;

	d = gui->win.disp_size;
	i = 0;
	while (i < count)
	{
		draw_insp_row(gui, pos, sl[i]);
		pos.y += ui_sy(INSP_ROW_STEP, d);
		i++;
	}
}
