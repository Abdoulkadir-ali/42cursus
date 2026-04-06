/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 06:25:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 10:34:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

void	widget_draw_label(t_gui *gui, t_widget *w)
{
	if (w->label)
		mlx_string_put(gui->win.mlx, gui->win.win, w->pos.x, w->pos.y
			+ w->size.y / 2, COL_TEXT, w->label);
	else
		mlx_string_put(gui->win.mlx, gui->win.win, w->pos.x, w->pos.y
			+ w->size.y / 2, COL_TEXT, "");
}

void	widget_draw_checkbox(t_gui *gui, t_widget *w)
{
	char	buf[128];

	if (w->value)
		buf[0] = 'X';
	else
		buf[0] = ' ';
	buf[1] = '\0';
	if (w->label)
		snprintf(buf + 2, sizeof(buf) - 2, "] %s", w->label);
	else
		snprintf(buf + 2, sizeof(buf) - 2, "]");
	mlx_string_put(gui->win.mlx, gui->win.win, w->pos.x, w->pos.y + w->size.y
		/ 2, COL_TEXT, buf);
}

static void	draw_widget_title(t_gui *gui, t_widget *w)
{
	t_panel	tb;

	if (!w->draggable)
		return ;
	tb.pos = w->pos;
	tb.size = vec2i(w->size.x, WIDGET_TITLE_H);
	tb.bg = 0x1A1A2A;
	tb.brd = COL_BORDER;
	draw_panel(gui, tb);
	if (w->label)
		gui_draw_string(gui, w->label,
			vec2i(w->pos.x + 6, w->pos.y + 5), COL_TEXT);
}

static void	dispatch_draw(t_gui *gui, t_widget *w)
{
	if (w->type == WIDGET_MESSAGE_BOX)
	{
		if (w->visible)
			widget_draw_msgbox(gui, w);
		return ;
	}
	draw_widget_title(gui, w);
	if (w->type == WIDGET_CHECKBOX)
		widget_draw_checkbox(gui, w);
	else if (w->type == WIDGET_LABEL)
		widget_draw_label(gui, w);
	else if (w->type == WIDGET_SLIDER)
		widget_draw_slider(gui, w);
	else if (w->type == WIDGET_INPUT_BOX)
		widget_draw_input(gui, w);
	else if (w->type == WIDGET_BUTTON)
		widget_draw_button(gui, w);
	else if (w->type == WIDGET_TOGGLE)
		widget_draw_toggle(gui, w);
	else if (w->type == WIDGET_PROGRESS_BAR)
		widget_draw_progress(gui, w);
	else if (w->type == WIDGET_SEPARATOR)
		widget_draw_separator(gui, w);
}

void	widget_draw_all(t_gui *gui)
{
	t_widget	*w;

	w = gui->widgets;
	while (w)
	{
		dispatch_draw(gui, w);
		w = w->next;
	}
}
