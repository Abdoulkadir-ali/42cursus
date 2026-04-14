/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 17:42:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"

bool	try_radio_click(t_gui *gui, t_vec2i mouse, t_panel pan, t_iradio r)
{
	int	ex;

	ex = pan.pos.x + pan.size.x;
	if (mouse.x < pan.pos.x || mouse.x >= ex)
		return (false);
	if (mouse.y < pan.pos.y || mouse.y >= pan.pos.y + SETTINGS_ROW_H)
		return (false);
	*r.ptr = !*r.ptr;
	if (r.on_change)
		r.on_change(gui);
	gui->render.dirty = true;
	return (true);
}

bool	try_settings_slider_click(t_gui *gui, t_vec2i mouse,
				t_vec2i pos, t_islider sl)
{
	int	track_w;
	int	track_y;

	track_w = SETTINGS_W - 32;
	track_y = pos.y + 10;
	if (mouse.x < pos.x || mouse.x >= (pos.x + track_w))
		return (false);
	if (mouse.y < track_y || mouse.y >= (track_y + 16))
		return (false);
	gui->slider_state.dragging = true;
	gui->slider_state.drag_start.x = mouse.x;
	gui->slider_state.drag_start_val = *sl.ptr;
	gui->slider_state.value_ptr = sl.ptr;
	gui->slider_state.dmin = sl.min;
	gui->slider_state.dmax = sl.max;
	gui->slider_state.track_x = pos.x;
	gui->slider_state.track_w = track_w;
	gui->slider_state.on_change = sl.on_change;
	return (true);
}
