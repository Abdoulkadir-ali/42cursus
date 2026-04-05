/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 19:14:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_slider_row(t_gui *gui, t_vec2i pos, t_islider sl)
{
	t_vec2i	d;
	char	buf[64];
	double	frac;
	int		fill_w;
	int		track_w;

	d = gui->win.disp_size;
	track_w = (int)gui->inspector.width - ui_sx(24, d);
	frac = 0.0;
	if (sl.max > sl.min)
		frac = (*sl.ptr - sl.min) / (sl.max - sl.min);
	if (frac < 0.0)
		frac = 0.0;
	if (frac > 1.0)
		frac = 1.0;
	fill_w = frac * track_w;
	snprintf(buf, sizeof(buf), "%.3f", *sl.ptr);
	mlx_string_put(gui->win.mlx, gui->win.win,
		pos.x, pos.y, COL_TEXT, (char *)sl.label);
	mlx_string_put(gui->win.mlx, gui->win.win,
		pos.x + track_w - ui_sx(46, d), pos.y, COL_HOVER, buf);
	draw_slider_fill(gui, vec2i(pos.x, pos.y + ui_sy(13, d)), fill_w, track_w);
}

bool	try_islider_click(t_gui *gui, t_vec2i mouse, t_vec2i pos,
		t_islider sl)
{
	t_vec2i	d;
	int		track_w;
	int		track_y;

	d = gui->win.disp_size;
	track_w = (int)gui->inspector.width - ui_sx(24, d);
	track_y = pos.y + ui_sy(9, d);
	if (mouse.x < (size_t)pos.x || mouse.x >= (size_t)(pos.x + track_w))
		return (false);
	if (mouse.y < (size_t)track_y || mouse.y >= (size_t)(track_y + 16))
		return (false);
	gui->slider_state.dragging = true;
	gui->slider_state.drag_start_x = mouse.x;
	gui->slider_state.drag_start_val = *sl.ptr;
	gui->slider_state.value_ptr = sl.ptr;
	gui->slider_state.dmin = sl.min;
	gui->slider_state.dmax = sl.max;
	gui->slider_state.track_x = pos.x;
	gui->slider_state.track_w = track_w;
	gui->slider_state.on_change = sl.on_change;
	return (true);
}
