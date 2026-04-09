/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 21:02:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include <math.h>

double	islider_get_val(t_islider sl)
{
	if (sl.ptr)
		return (*sl.ptr);
	return (0.0);
}

double	sl_to_frac(double val, double dmin, double dmax)
{
	double	range;

	range = dmax - dmin;
	if (range < 1e3 || dmin < 0.0)
		return ((val - dmin) / range);
	return (log(val - dmin + 1.0) / log(range + 1.0));
}

double	sl_from_frac(double frac, double dmin, double dmax)
{
	double	range;

	if (frac < 0.0)
		frac = 0.0;
	if (frac > 1.0)
		frac = 1.0;
	range = dmax - dmin;
	if (range < 1e3 || dmin < 0.0)
		return (dmin + frac * range);
	return (dmin + exp(frac * log(range + 1.0)) - 1.0);
}

void	islider_set_val(t_islider sl, double v)
{
	if (sl.ptr)
		*sl.ptr = v;
}

void	draw_slider_row(t_gui *gui, t_vec2i pos, t_islider sl)
{
	t_vec2s	d;
	char	buf[64];
	double	frac;
	int		fill_w;
	int		track_w;

	d = gui->win.disp_size;
	track_w = gui->inspector.width - ui_sx(24, d);
	frac = 0.0;
	if (sl.max > sl.min)
		frac = sl_to_frac(islider_get_val(sl), sl.min, sl.max);
	if (frac < 0.0)
		frac = 0.0;
	if (frac > 1.0)
		frac = 1.0;
	fill_w = frac * track_w;
	snprintf(buf, sizeof(buf), "%.4g", islider_get_val(sl));
	mlx_string_put_c(gui->win.mlx, gui->win.win,
		pos.x, pos.y, COL_TEXT, sl.label);
	mlx_string_put_c(gui->win.mlx, gui->win.win,
		pos.x + track_w - ui_sx(46, d), pos.y, COL_HOVER, buf);
	draw_slider_fill(gui, vec2i(pos.x, pos.y + ui_sy(13, d)), fill_w, track_w);
}

bool	try_islider_click(t_gui *gui, t_vec2i mouse, t_vec2i pos,
		t_islider sl)
{
	t_vec2s	d;
	int		track_w;
	int		track_y;

	d = gui->win.disp_size;
	track_w = gui->inspector.width - ui_sx(24, d);
	track_y = pos.y + ui_sy(9, d);
	if (mouse.x < pos.x || mouse.x >= (pos.x + track_w))
		return (false);
	if (mouse.y < track_y || mouse.y >= (track_y + ui_sy(16, d)))
		return (false);
	gui->slider_state.dragging = true;
	gui->slider_state.drag_start.x = mouse.x;
	gui->slider_state.drag_start_val = islider_get_val(sl);
	gui->slider_state.value_ptr = sl.ptr;
	gui->slider_state.dmin = sl.min;
	gui->slider_state.dmax = sl.max;
	gui->slider_state.track_x = pos.x;
	gui->slider_state.track_w = track_w;
	gui->slider_state.on_change = sl.on_change;
	return (true);
}
