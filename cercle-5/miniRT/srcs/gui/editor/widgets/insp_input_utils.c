/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insp_input_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 11:01:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	set_insp_drag(t_gui *gui, t_islider sl, int mouse_x, int tx, int tw)
{
	gui->slider_state.dragging = true;
	gui->slider_state.drag_start.x = mouse_x;
	gui->slider_state.drag_start_val = *sl.ptr;
	gui->slider_state.value_ptr = sl.ptr;
	gui->slider_state.dmin = sl.min;
	gui->slider_state.dmax = sl.max;
	gui->slider_state.track_x = tx;
	gui->slider_state.track_w = tw;
	gui->slider_state.on_change = sl.on_change;
}

void	set_insp_edit(t_gui *gui, t_islider sl)
{
	t_insp_edit	*e;

	e = &gui->slider_state.insp_edit;
	e->active = true;
	e->value_ptr = sl.ptr;
	e->dmin = sl.min;
	e->dmax = sl.max;
	e->on_change = sl.on_change;
	snprintf(e->buf, sizeof(e->buf), "%.6g", *sl.ptr);
	e->i = ft_strlen(e->buf);
}

void	insp_input_commit(t_gui *gui)
{
	t_insp_edit	*e;
	double		val;

	e = &gui->slider_state.insp_edit;
	val = strtod(e->buf, NULL);
	if (val < e->dmin)
		val = e->dmin;
	if (val > e->dmax)
		val = e->dmax;
	*e->value_ptr = val;
	if (e->on_change)
		e->on_change(gui);
	gui->render.dirty = true;
	gui->render.bvh_needs_rebuild = 1;
	e->active = false;
	e->value_ptr = NULL;
}

bool	insp_input_nav(t_insp_edit *e, int keycode)
{
	if (keycode == XK_Left)
	{
		if (e->cursor > 0)
			e->cursor--;
	}
	else if (keycode == XK_Right)
	{
		if (e->cursor < ft_strlen(e->buf))
			e->cursor++;
	}
	else if (keycode == XK_Home)
		e->cursor = 0;
	else if (keycode == XK_End)
		e->cursor = ft_strlen(e->buf);
	else
		return (false);
	return (true);
}
