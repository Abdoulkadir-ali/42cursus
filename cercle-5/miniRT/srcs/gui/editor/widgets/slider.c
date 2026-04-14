/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 01:38:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include <math.h>

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

	range = dmax - dmin;
	if (frac < 0.0)
		frac = 0.0;
	if (frac > 1.0)
		frac = 1.0;
	if (range < 1e3 || dmin < 0.0)
		return (dmin + frac * range);
	return (dmin + exp(frac * log(range + 1.0)) - 1.0);
}

void	draw_slider_row(t_gui *gui, t_vec2i pos, t_islider sl)
{
	t_vec2s	d;
	char	buf[64];
	double	f;
	double	v;
	int		tr_w;

	d = gui->win.disp_size;
	tr_w = gui->inspector.width - ui_sx(24, d);
	f = 0.0;
	v = 0.0;
	if (sl.ptr)
	{
		v = *sl.ptr;
		if (sl.max > sl.min)
			f = fmax(0.0, fmin(1.0, sl_to_frac(v, sl.min, sl.max)));
	}
	snprintf(buf, sizeof(buf), "%.4g", v);
	mlx_string_put_c(gui->win.mlx, gui->win.win, pos.x, pos.y, COL_TEXT,
		sl.label);
	mlx_string_put_c(gui->win.mlx, gui->win.win, pos.x + tr_w - ui_sx(46, d),
		pos.y, COL_HOVER, buf);
	draw_slider_fill(gui, vec2i(pos.x, pos.y + ui_sy(13, d)), f * tr_w, tr_w);
}

bool	try_islider_click(t_gui *gui, t_vec2i mouse, t_vec2i pos, t_islider sl)
{
	t_vec2s	d;
	int		t[2];

	d = gui->win.disp_size;
	t[0] = gui->inspector.width - ui_sx(24, d);
	t[1] = pos.y + ui_sy(9, d);
	if (!sl.ptr || mouse.x < pos.x || mouse.x >= (pos.x + t[0])
		|| mouse.y < t[1] || mouse.y >= (t[1] + ui_sy(16, d)))
		return (false);
	gui->slider_state.dragging = true;
	gui->slider_state.drag_start.x = mouse.x;
	gui->slider_state.drag_start_val = *sl.ptr;
	gui->slider_state.value_ptr = sl.ptr;
	gui->slider_state.dmin = sl.min;
	gui->slider_state.dmax = sl.max;
	gui->slider_state.track_x = pos.x;
	gui->slider_state.track_w = t[0];
	gui->slider_state.on_change = sl.on_change;
	return (true);
}

double	islider_get_val(t_islider sl)
{
	if (!sl.ptr)
		return (0.0);
	return (*sl.ptr);
}
