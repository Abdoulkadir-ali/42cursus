/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 23:45:22 by abdoali          ###   ########.fr       */
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
	delta = (double)((int)mouse.x - gui->slider_state.drag_start_x)
		* range / (double)gui->slider_state.track_w;
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
	gui->render.mesh_transform_pending = 1;
	{ t_cmd _c; ft_memset(&_c, 0, sizeof(_c)); _c.type = CMD_REBUILD_BVH; cmd_enqueue(gui, _c); }
}
