/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 13:01:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

void	slider_begin_drag(t_gui *gui, t_widget *w, int mouse_x)
{
	gui->slider_state.dragging = true;
	gui->slider_state.target = w;
	gui->slider_state.drag_start_x = mouse_x;
	gui->slider_state.drag_start_val = w->dvalue;
}

void	slider_update_drag(t_gui *gui, int mouse_x)
{
	t_widget	*w;
	double		range;
	double		delta;
	double		newval;

	if (!gui->slider_state.dragging || !gui->slider_state.target)
		return ;
	w = gui->slider_state.target;
	range = w->dmax - w->dmin;
	delta = (double)(mouse_x - gui->slider_state.drag_start_x)
		* range / (double)w->size.x;
	newval = gui->slider_state.drag_start_val + delta;
	if (newval < w->dmin)
		newval = w->dmin;
	if (newval > w->dmax)
		newval = w->dmax;
	w->dvalue = newval;
	if (w->target)
		*(double *)w->target = newval;
	if (w->on_change)
		w->on_change(w, gui);
	gui->render.dirty = true;
}

void	slider_end_drag(t_gui *gui)
{
	gui->slider_state.dragging = false;
	gui->slider_state.target = NULL;
}
