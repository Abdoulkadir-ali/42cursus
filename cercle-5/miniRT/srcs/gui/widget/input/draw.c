/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 10:46:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

static void	draw_input_cursor(t_gui *gui, t_widget *w, t_vec2i tpos)
{
	t_panel	cursor;
	int		cx;

	cx = tpos.x + w->cursor_pos * 8;
	cursor = (t_panel){
		.pos = vec2i(cx, tpos.y - 1),
		.size = vec2i(1, 10),
		.bg = COL_ACCENT, .brd = COL_ACCENT};
	draw_panel(gui, cursor);
}

void	widget_draw_input(t_gui *gui, t_widget *w)
{
	t_panel	bg;
	t_vec2i	tpos;
	int		brd;

	brd = COL_BORDER;
	if (w->focused)
		brd = COL_ACCENT;
	bg = (t_panel){.pos = w->pos, .size = w->size, .bg = 0x0E0E1A, .brd = brd};
	draw_panel(gui, bg);
	if (w->label)
		gui_draw_string(gui, w->label,
			vec2i(w->pos.x, (int)w->pos.y - 12), COL_TEXT);
	tpos = vec2i(w->pos.x + 4, (int)w->pos.y + w->size.y / 2 - 4);
	gui_draw_string(gui, w->input_buf, tpos, COL_TEXT);
	if (w->focused)
		draw_input_cursor(gui, w, tpos);
}
