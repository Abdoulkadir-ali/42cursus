/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 21:02:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	update_inline_drag(t_gui *gui, t_vec2i mouse)
{
	double	frac;
	double	newval;

	if (!gui->slider_state.dragging || !gui->slider_state.value_ptr)
		return ;
	frac = (double)(mouse.x - gui->slider_state.drag_start.x)
		/ (double)gui->slider_state.track_w;
	frac += sl_to_frac(gui->slider_state.drag_start_val,
			gui->slider_state.dmin, gui->slider_state.dmax);
	newval = sl_from_frac(frac,
			gui->slider_state.dmin, gui->slider_state.dmax);
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
