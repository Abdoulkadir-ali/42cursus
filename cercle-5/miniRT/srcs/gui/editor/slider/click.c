/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 17:16:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
/**
 * @brief Checks and initiates a slider drag if the click was on the track area.
 * @param gui Pointer to the GUI context.
 * @param mouse The click coordinates.
 * @param arg Slider configuration structure.
 * @return true if the click hit the slider.
 */
bool	try_islider_click(t_gui *gui, t_vec2i mouse, t_slider_arg arg)
{
	int	rx;

	rx = mouse.x - arg.pos.x;
	if (rx < 0 || rx > INSPECTOR_W - 24)
		return (false);
	if (!arg.sl.prop)
		return (false);
	gui->slider_state->dragging = true;
	gui->slider_state->drag_start_x = mouse.x;
	gui->slider_state->prop = arg.sl.prop;
	gui->slider_state->obj_index = gui->selection->index;
	gui->slider_state->drag_start_val = arg.sl.prop->get(gui->scene,
		gui->slider_state->obj_index);
	gui->slider_state->dmin = arg.sl.min;
	gui->slider_state->dmax = arg.sl.max;
	if (gui->slider_state->dmin == 0 && gui->slider_state->dmax == 0)
	{
		gui->slider_state->dmin = arg.sl.prop->min;
		gui->slider_state->dmax = arg.sl.prop->max;
	}
	gui->slider_state->track_x = arg.pos.x;
	gui->slider_state->track_w = INSPECTOR_W - 24;
	gui->slider_state->on_change = arg.on_change;
	gui->slider_state->target = NULL;
	return (true);
}
