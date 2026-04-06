/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	update_inline_drag(t_gui *gui, t_vec2i mouse)
{
	double	range;
	double	delta;
	double	newval;

	if (!gui->slider_state.dragging || !gui->slider_state.value_ptr)
		return ;
	range = gui->slider_state.dmax - gui->slider_state.dmin;
	delta = (double)(mouse.x - gui->slider_state.drag_start.x);
	delta = delta * range / (double)gui->slider_state.track_w;
	newval = gui->slider_state.drag_start_val + delta;
	if (newval < gui->slider_state.dmin)
		newval = gui->slider_state.dmin;
	if (newval > gui->slider_state.dmax)
		newval = gui->slider_state.dmax;
	*gui->slider_state.value_ptr = newval;
	gui->render.dirty = true;
}

void	end_inline_drag(t_gui *gui)
{
	if (!gui->slider_state.dragging)
		return ;
	gui->slider_state.dragging = false;
	gui->slider_state.value_ptr = NULL;
	if (gui->slider_state.on_change)
		gui->slider_state.on_change(gui);
	gui->slider_state.on_change = NULL;
	gui->render.bvh_needs_rebuild = 1;
}
