/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 17:09:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

static void	draw_input_cursor(t_gui *gui, t_widget *w, t_vec2i tpos)
{
	t_panel	cursor;
	int		cx;

	cx = tpos.x + w->cursor_pos * 8;
	cursor.pos = vec2i(cx, tpos.y - 1);
	cursor.size = vec2s(1, 10);
	cursor.bg = COL_ACCENT;
	cursor.brd = COL_ACCENT;
	cursor.lbl = NULL;
	draw_panel(gui, cursor);
}

static void	draw_input_bg(t_gui *gui, t_widget *w)
{
	t_panel	bg;

	bg.pos = w->pos;
	bg.size = w->size;
	bg.bg = COL_INPUT_BG;
	bg.brd = COL_BORDER;
	if (w->focused)
		bg.brd = COL_ACCENT;
	bg.lbl = NULL;
	draw_panel(gui, bg);
}

void	widget_draw_input(t_gui *gui, t_widget *w)
{
	t_vec2i	tpos;

	if (!w->visible)
		return ;
	draw_input_bg(gui, w);
	if (w->label)
		gui_draw_string(gui, w->label,
			vec2i(w->pos.x, w->pos.y - 12), COL_TEXT);
	tpos = vec2i(w->pos.x + 4, w->pos.y + w->size.y / 2 - 4);
	gui_draw_string(gui, w->input_buf, tpos, COL_TEXT);
	if (w->focused)
		draw_input_cursor(gui, w, tpos);
}
