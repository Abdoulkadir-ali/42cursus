/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 06:25:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 03:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

static void	draw_w_text_fill_buf(char *buf, t_widget *w)
{
	if (w->value)
		ft_memcpy(buf, "[X] ", 5);
	else
		ft_memcpy(buf, "[ ] ", 5);
	if (w->label)
		snprintf(buf + 4, 124, "%s", w->label);
	else
		buf[4] = '\0';
}

static void	draw_w_text(t_gui *gui, t_widget *w)
{
	char		buf[128];
	int			y;
	const char	*lbl;

	y = w->pos.y + w->size.y / 2;
	if (w->type == WIDGET_LABEL)
	{
		lbl = "";
		if (w->label)
			lbl = w->label;
		mlx_string_put_c(gui->win.mlx, gui->win.win, w->pos.x, y,
			COL_TEXT, lbl);
	}
	else if (w->type == WIDGET_CHECKBOX)
	{
		draw_w_text_fill_buf(buf, w);
		mlx_string_put_c(gui->win.mlx, gui->win.win, w->pos.x, y,
			COL_TEXT, buf);
	}
}

static void	draw_widget_title(t_gui *gui, t_widget *w)
{
	t_panel	tb;

	if (!w->draggable)
		return ;
	tb.pos = w->pos;
	tb.size = vec2s(w->size.x, WIDGET_TITLE_H);
	tb.bg = 0x1A1A2A;
	tb.brd = COL_BORDER;
	draw_panel(gui, tb);
	if (w->label)
		gui_draw_string(gui, w->label,
			vec2i(w->pos.x + 6, w->pos.y + 5), COL_TEXT);
}

static void	dispatch_type(t_gui *gui, t_widget *w)
{
	if (w->type == WIDGET_CHECKBOX || w->type == WIDGET_LABEL)
		draw_w_text(gui, w);
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
		if (w->type == WIDGET_MESSAGE_BOX)
		{
			if (w->visible)
				widget_draw_msgbox(gui, w);
		}
		else
		{
			draw_widget_title(gui, w);
			dispatch_type(gui, w);
		}
		w = w->next;
	}
}
