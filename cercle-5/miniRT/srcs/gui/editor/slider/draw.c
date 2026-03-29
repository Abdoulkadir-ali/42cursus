/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 20:31:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
/**
 * @brief Renders the slider track, filled progress, and interactive knob.
 * @param gui Pointer to the GUI context.
 * @param x/y Starting coordinates of the track.
 * @param fill_w Current width of the filled (active) area.
 * @param total_w Total width of the track.
 */
static void	draw_slider_fill(t_gui *gui, int x, int y, int fill_w, int total_w)
{
	int	kx;

	fill_rect(gui, x, y, total_w, SLIDER_H, COL_SLIDER_BG);
	fill_rect(gui, x, y, total_w, 1, COL_BORDER);
	fill_rect(gui, x, y + SLIDER_H - 1, total_w, 1, COL_BORDER);
	if (fill_w > 0)
		fill_rect(gui, x, y, fill_w, SLIDER_H, COL_SLIDER_FG);
	kx = x + fill_w - 1;
	if (kx < x)
		kx = x;
	fill_rect(gui, kx, y - 2, SLIDER_KNOB_W, SLIDER_KNOB_H, 0xE0E0E0U);
}

/**
 * @brief Draws a single slider row with its label, value, track, and knob.
 * @param gui Pointer to the GUI context.
 * @param arg Slider configuration structure.
 */
void	draw_slider_row(t_gui *gui, t_slider_arg arg)
{
	char	buf[64];
	double	value;
	double	frac;
	int		fill_w;
	int		track_w;
	double	min;
	double	max;
	const char *label;

	if (!arg.sl.prop)
		return ;
	min = arg.sl.min;
	max = arg.sl.max;
	label = arg.sl.label;
	if (arg.sl.prop)
	{
		value = arg.sl.prop->get(gui->scene, gui->selection->index);
		if (min == 0 && max == 0)
		{
			min = arg.sl.prop->min;
			max = arg.sl.prop->max;
		}
		if (!label)
			label = arg.sl.prop->name;
	}
	track_w = INSPECTOR_W - SLIDER_PAD;
	frac = (value - min) / (max - min);
	if (frac < 0.0)
		frac = 0.0;
	if (frac > 1.0)
		frac = 1.0;
	fill_w = (int)(frac * track_w);
	snprintf(buf, sizeof(buf), "%.3f", value);
	gui_draw_string(gui, (char *)label, arg.pos.x, arg.pos.y, COL_TEXT);
	gui_draw_string(gui, buf, arg.pos.x + track_w
		- SLIDER_VAL_X, arg.pos.y, COL_HOVER);
	draw_slider_fill(gui, arg.pos.x, arg.pos.y + SLIDER_Y_OFF,
		fill_w, track_w);
}
