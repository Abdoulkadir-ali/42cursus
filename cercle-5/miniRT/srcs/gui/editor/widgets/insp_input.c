/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insp_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 19:10:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include <X11/keysym.h>
#include <stdlib.h>

bool	insp_row_click(t_gui *gui, t_vec2i mouse, t_vec2i pos, t_islider sl)
{
	t_vec2i	d;
	int		sx;
	int		ix;
	int		sl_w;
	int		in_w;
	int		row_h;

	d = gui->win.disp_size;
	sl_w = ui_sx(INSP_SL_W, d);
	in_w = ui_sx(INSP_IN_W, d);
	row_h = ui_sy(INSP_ROW_STEP, d);
	sx = pos.x + ui_sx(INSP_SL_OFF, d);
	ix = pos.x + ui_sx(INSP_IN_OFF, d);
	if ((int)mouse.x >= sx && (int)mouse.x < sx + sl_w
		&& (int)mouse.y >= (int)pos.y && (int)mouse.y < (int)pos.y + row_h)
	{
		gui->slider_state.dragging = true;
		gui->slider_state.drag_start_x = mouse.x;
		gui->slider_state.drag_start_val = *sl.ptr;
		gui->slider_state.value_ptr = sl.ptr;
		gui->slider_state.dmin = sl.min;
		gui->slider_state.dmax = sl.max;
		gui->slider_state.track_x = sx;
		gui->slider_state.track_w = sl_w;
		gui->slider_state.on_change = sl.on_change;
		return (true);
	}
	if ((int)mouse.x >= ix && (int)mouse.x < ix + in_w
		&& (int)mouse.y >= (int)pos.y && (int)mouse.y < (int)pos.y + row_h)
	{
		gui->slider_state.insp_edit.active = true;
		gui->slider_state.insp_edit.value_ptr = sl.ptr;
		gui->slider_state.insp_edit.dmin = sl.min;
		gui->slider_state.insp_edit.dmax = sl.max;
		gui->slider_state.insp_edit.on_change = sl.on_change;
		snprintf(gui->slider_state.insp_edit.buf,
			sizeof(gui->slider_state.insp_edit.buf), "%.6g", *sl.ptr);
		gui->slider_state.insp_edit.cursor =
			(int)ft_strlen(gui->slider_state.insp_edit.buf);
		return (true);
	}
	return (false);
}

bool	insp_toggle_click(t_gui *gui, t_vec2i mouse, t_vec2i pos)
{
	t_vec2i	d;
	int		ix;

	d = gui->win.disp_size;
	ix = pos.x + ui_sx(INSP_IN_OFF, d);
	return ((int)mouse.x >= ix && (int)mouse.x < ix + ui_sx(INSP_IN_W, d)
		&& (int)mouse.y >= (int)pos.y
		&& (int)mouse.y < (int)pos.y + ui_sy(INSP_ROW_STEP, d));
}

static void	insp_input_commit(t_gui *gui)
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

static bool	insp_input_nav(t_insp_edit *e, int keycode)
{
	int	len;

	if (keycode == XK_Left)
	{
		if (e->cursor > 0)
			e->cursor--;
		return (true);
	}
	if (keycode == XK_Right)
	{
		len = (int)ft_strlen(e->buf);
		if (e->cursor < len)
			e->cursor++;
		return (true);
	}
	if (keycode == XK_Home)
	{
		e->cursor = 0;
		return (true);
	}
	if (keycode == XK_End)
	{
		e->cursor = (int)ft_strlen(e->buf);
		return (true);
	}
	return (false);
}

static void	insp_input_edit(t_gui *gui, int keycode)
{
	t_insp_edit	*e;
	int			i;

	e = &gui->slider_state.insp_edit;
	if (keycode == XK_BackSpace && e->cursor > 0)
	{
		i = e->cursor - 1;
		while (e->buf[i])
		{
			e->buf[i] = e->buf[i + 1];
			i++;
		}
		e->cursor--;
		return ;
	}
	if ((keycode >= '0' && keycode <= '9')
		|| keycode == '.' || keycode == '-'
		|| keycode == 'e' || keycode == 'E')
	{
		if ((int)ft_strlen(e->buf) >= 30)
			return ;
		i = (int)ft_strlen(e->buf);
		while (i >= e->cursor)
		{
			e->buf[i + 1] = e->buf[i];
			i--;
		}
		e->buf[e->cursor] = (char)keycode;
		e->cursor++;
	}
}

void	insp_input_key(t_gui *gui, int keycode)
{
	t_insp_edit	*e;

	e = &gui->slider_state.insp_edit;
	if (!e->active)
		return ;
	if (keycode == XK_Escape)
	{
		e->active = false;
		e->value_ptr = NULL;
		return ;
	}
	if (keycode == XK_Return || keycode == XK_KP_Enter)
	{
		insp_input_commit(gui);
		return ;
	}
	if (!insp_input_nav(e, keycode))
		insp_input_edit(gui, keycode);
}
