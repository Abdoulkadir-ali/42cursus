/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 12:33:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

static double	get_slider_frac(t_widget *w)
{
	double	frac;

	frac = 0.0;
	if (w->dmax > w->dmin)
		frac = (w->dvalue - w->dmin) / (w->dmax - w->dmin);
	if (frac < 0.0)
		frac = 0.0;
	if (frac > 1.0)
		frac = 1.0;
	return (frac);
}

static void	draw_slider_track(t_gui *gui, t_widget *w)
{
	t_panel	track;
	t_panel	fill;
	int		fill_w;

	fill_w = get_slider_frac(w) * w->size.x;
	track = (t_panel){
		.pos = vec2i(w->pos.x, w->pos.y + w->size.y / 2 - 3),
			.size = vec2s(w->size.x, 6),
		.bg = COL_SLIDER_BG, .brd = COL_BORDER};
	draw_panel(gui, track);
	if (fill_w > 0)
	{
		fill = (t_panel){
			.pos = vec2i(w->pos.x, w->pos.y + w->size.y / 2 - 3),
			.size = vec2s(fill_w, 6),
			.bg = COL_SLIDER_FG, .brd = COL_SLIDER_FG};
		draw_panel(gui, fill);
	}
}

void	widget_draw_slider(t_gui *gui, t_widget *w)
{
	char	buf[64];

	draw_slider_track(gui, w);
	if (w->label)
		mlx_string_put(gui->win.mlx, gui->win.win,
			w->pos.x, w->pos.y + 2, COL_TEXT, w->label);
	snprintf(buf, sizeof(buf), "%.3f", w->dvalue);
	mlx_string_put(gui->win.mlx, gui->win.win,
		w->pos.x + w->size.x - 48, w->pos.y + 2, COL_HOVER, buf);
}
