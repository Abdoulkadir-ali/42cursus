/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/07 21:13:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"

static void	draw_slider_track(t_gui *gui, t_widget *w)
{
	t_panel	track;
	t_panel	fill;
	double	frac;
	int		fill_w;

	frac = 0.0;
	if (w->dmax > w->dmin)
		frac = (w->dvalue - w->dmin) / (w->dmax - w->dmin);
	if (frac < 0.0)
		frac = 0.0;
	if (frac > 1.0)
		frac = 1.0;
	fill_w = (int)(frac * w->size.x);
	track = (t_panel){.x = w->pos.x, .y = w->pos.y + w->size.y / 2 - 3,
		.w = w->size.x, .h = 6, .bg = COL_SLIDER_BG, .brd = COL_BORDER,
		.pos = w->pos, .size = vec2i(w->size.x, 6)};
	draw_panel(gui, track);
	if (fill_w > 0)
	{
		fill = (t_panel){.x = w->pos.x, .y = w->pos.y + w->size.y / 2 - 3,
			.w = fill_w, .h = 6, .bg = COL_SLIDER_FG, .brd = COL_SLIDER_FG,
			.pos = w->pos, .size = vec2i(fill_w, 6)};
		draw_panel(gui, fill);
	}
}

static void	draw_slider_label(t_gui *gui, t_widget *w)
{
	char	buf[64];

	if (w->label)
		mlx_string_put(gui->win.mlx, gui->win.win,
			w->pos.x, w->pos.y + 2, COL_TEXT, w->label);
	snprintf(buf, sizeof(buf), "%.3f", w->dvalue);
	mlx_string_put(gui->win.mlx, gui->win.win,
		w->pos.x + w->size.x - 48, w->pos.y + 2, COL_HOVER, buf);
}

void	widget_draw_slider(t_gui *gui, t_widget *w)
{
	draw_slider_track(gui, w);
	draw_slider_label(gui, w);
}

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

bool	slider_handle_click(t_gui *gui, t_widget *w, t_vec2i mouse)
{
	if (mouse.x < w->pos.x || mouse.x >= w->pos.x + w->size.x)
		return (false);
	if (mouse.y < w->pos.y || mouse.y >= w->pos.y + w->size.y)
		return (false);
	slider_begin_drag(gui, w, mouse.x);
	return (true);
}
