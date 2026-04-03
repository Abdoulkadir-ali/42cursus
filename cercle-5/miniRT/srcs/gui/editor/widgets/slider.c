/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 15:05:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	fill_rect_row(t_gui *gui, t_vec2i pos, int w, unsigned int col)
{
	char	*dst;
	int		i;

	if (pos.y >= gui->win.disp_size.y)
		return ;
	i = 0;
	while (i < w)
	{
		if ((size_t)(pos.x + i) < gui->win.disp_size.x)
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
	size_t	j;

	j = 0;
	while (j < (size_t)size.y)
	{
		fill_rect_row(gui, vec2i(pos.x, pos.y + (int)j), size.x, col);
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
	if (knob_x < (int)pos.x)
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
		t_islider sl)
{
	int	track_w;
	int	track_y;

	track_w = INSPECTOR_W - 24;
	track_y = pos.y + 9;
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
