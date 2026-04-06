/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 23:42:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

/*
** Draws a labeled ON/OFF radio row.
** The toggle button is right-aligned inside a band of width w.
*/
void	draw_radio_row(t_gui *gui, t_panel pan, t_iradio r)
{
	int			btn_x;
	int			bg;
	int			col;
	const char	*status;

	btn_x = pan.pos.x + (int)pan.size.x - 44 - 4;
	bg = 0x2A1616;
	col = 0x804040;
	status = "OFF";
	if (*r.ptr)
	{
		bg = 0x0E2E18;
		col = 0x20D860;
		status = "ON";
	}
	mlx_string_put(gui->win.mlx, gui->win.win,
		pan.pos.x + 8, pan.pos.y + 15, COL_TEXT, (char *)r.label);
	draw_panel(gui, (t_panel){vec2i(btn_x, pan.pos.y + 4),
		vec2i(44, 20), bg, col, ""});
	mlx_string_put(gui->win.mlx, gui->win.win,
		btn_x + 10, pan.pos.y + 18, col, (char *)status);
}

bool	try_radio_click(t_gui *gui, t_vec2i mouse, t_panel pan, t_iradio r)
{
	if (mouse.x < pan.pos.x || mouse.x >= pan.pos.x + pan.size.x)
		return (false);
	if (mouse.y < pan.pos.y || mouse.y >= pan.pos.y + (size_t)SETTINGS_ROW_H)
		return (false);
	*r.ptr = !*r.ptr;
	if (r.on_change)
		r.on_change(gui);
	gui->render.dirty = true;
	return (true);
}

/*
** Draws a labeled slider row sized to the settings panel width.
*/
void	draw_settings_slider(t_gui *gui, t_vec2i pos, t_islider sl)
{
	char	buf[64];
	double	frac;
	int		fill_w;
	int		track_w;

	track_w = SETTINGS_W - 32;
	frac = 0.0;
	if (sl.max > sl.min)
		frac = (*sl.ptr - sl.min) / (sl.max - sl.min);
	if (frac < 0.0)
		frac = 0.0;
	if (frac > 1.0)
		frac = 1.0;
	fill_w = (int)(frac * track_w);
	snprintf(buf, sizeof(buf), "%.3g", *sl.ptr);
	mlx_string_put(gui->win.mlx, gui->win.win,
		pos.x, pos.y, COL_TEXT, (char *)sl.label);
	mlx_string_put(gui->win.mlx, gui->win.win,
		pos.x + track_w - 56, pos.y, COL_HOVER, buf);
	draw_slider_fill(gui, vec2i(pos.x, pos.y + 14), fill_w, track_w);
}

bool	try_settings_slider_click(t_gui *gui, t_vec2i mouse,
				t_vec2i pos, t_islider sl)
{
	int	track_w;
	int	track_y;

	track_w = SETTINGS_W - 32;
	track_y = pos.y + 10;
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
