/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:39:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	fill_rect_row(t_gui *gui, t_vec2i pos, int w, unsigned int col)
{
	char	*dst;
	int		i;

	if (pos.y < 0 || pos.y >= gui->win.disp_size.y)
		return ;
	i = 0;
	while (i < w)
	{
		if (pos.x + i >= 0 && pos.x + i < gui->win.disp_size.x)
		{
			dst = gui->win.disp_addr
				+ (pos.y * gui->win.disp_line_len + (pos.x + i) * 4);
			*(unsigned int *)dst = col;
		}
		i++;
	}
}

static void	fill_rect(t_gui *gui, t_vec2i pos, t_vec2i size, unsigned int col)
{
	int	j;

	j = 0;
	while (j < size.y)
	{
		fill_rect_row(gui, vec2i(pos.x, pos.y + j), size.x, col);
		j++;
	}
}

static void	draw_slider_fill(t_gui *gui, t_vec2i pos, int fill_w, int total_w)
{
	int	knob_x;

	fill_rect(gui, pos, vec2i(total_w, 8), (unsigned int)COL_SLIDER_BG);
	fill_rect(gui, pos, vec2i(total_w, 1), (unsigned int)COL_BORDER);
	fill_rect(gui, vec2i(pos.x, pos.y + 7), vec2i(total_w, 1),
		(unsigned int)COL_BORDER);
	if (fill_w > 0)
		fill_rect(gui, pos, vec2i(fill_w, 8), (unsigned int)COL_SLIDER_FG);
	knob_x = pos.x + fill_w - 1;
	if (knob_x < pos.x)
		knob_x = pos.x;
	fill_rect(gui, vec2i(knob_x, pos.y - 2), vec2i(3, 12), 0xE0E0E0U);
}

void	draw_slider_row(t_gui *gui, t_vec2i pos, t_islider sl)
{
	char	buf[64];
	double	frac;
	int		fill_w;
	int		track_w;

	track_w = INSPECTOR_W - 24;
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
		pos.x + track_w - 46, pos.y, COL_HOVER, buf);
	draw_slider_fill(gui, vec2i(pos.x, pos.y + 13), fill_w, track_w);
}

bool	try_islider_click(t_gui *gui, t_vec2i mouse, t_vec2i pos,
		t_islider sl, void (*on_change)(t_gui *gui))
{
	int	track_w;
	int	track_y;

	track_w = INSPECTOR_W - 24;
	track_y = pos.y + 9;
	if (mouse.x < pos.x || mouse.x >= pos.x + track_w)
		return (false);
	if (mouse.y < track_y || mouse.y >= track_y + 16)
		return (false);
	gui->slider_state.dragging = true;
	gui->slider_state.drag_start_x = mouse.x;
	gui->slider_state.drag_start_val = *sl.ptr;
	gui->slider_state.value_ptr = sl.ptr;
	gui->slider_state.dmin = sl.min;
	gui->slider_state.dmax = sl.max;
	gui->slider_state.track_x = pos.x;
	gui->slider_state.track_w = track_w;
	gui->slider_state.on_change = on_change;
	return (true);
}

void	update_inline_drag(t_gui *gui, t_vec2i mouse)
{
	double	range;
	double	delta;
	double	newval;

	if (!gui->slider_state.dragging || !gui->slider_state.value_ptr)
		return ;
	range = gui->slider_state.dmax - gui->slider_state.dmin;
	delta = (double)(mouse.x - gui->slider_state.drag_start_x)
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
	rebuild_bvh(gui);
	gui->render.dirty = true;
}
