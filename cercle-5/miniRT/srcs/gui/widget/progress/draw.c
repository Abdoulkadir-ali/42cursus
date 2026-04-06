/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 12:33:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

static void	draw_progress_fill(t_gui *gui, t_widget *w, double frac)
{
	t_panel	fill;
	int		fill_w;

	fill_w = (frac * w->size.x);
	if (fill_w <= 0)
		return ;
	fill = (t_panel){.pos = w->pos, .size = vec2s(fill_w, w->size.y),
		.bg = COL_ACCENT, .brd = COL_ACCENT};
	draw_panel(gui, fill);
}

void	widget_draw_progress(t_gui *gui, t_widget *w)
{
	t_panel	bg;
	double	frac;
	char	buf[32];

	bg = (t_panel){.pos = w->pos, .size = w->size,
		.bg = COL_SLIDER_BG, .brd = COL_BORDER};
	draw_panel(gui, bg);
	frac = w->progress;
	if (frac < 0.0)
		frac = 0.0;
	if (frac > 1.0)
		frac = 1.0;
	draw_progress_fill(gui, w, frac);
	snprintf(buf, sizeof(buf), "%.0f%%", frac * 100.0);
	gui_draw_string(gui, buf,
		vec2i(w->pos.x + w->size.x / 2 - 12,
			w->pos.y + w->size.y / 2 - 4), COL_TEXT);
	if (w->label)
		gui_draw_string(gui, w->label,
			vec2i(w->pos.x, w->pos.y - 12), COL_TEXT);
}
