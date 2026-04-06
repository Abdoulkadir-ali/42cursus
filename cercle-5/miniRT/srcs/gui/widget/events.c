/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 03:05:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

bool	hit_titlebar(t_widget *w, t_vec2i m);
bool	hit_body(t_widget *w, t_vec2i m);
bool	handle_msgbox_click(t_gui *gui, t_widget *w, t_vec2i m);

static void	handle_control_click(t_gui *gui, t_widget *w, t_vec2i mouse)
{
	if (w->type == WIDGET_INPUT_BOX)
	{
		w->focused = true;
		gui->focused_widget = w;
	}
	else if (w->type == WIDGET_SLIDER)
		slider_handle_click(gui, w, mouse);
	else if (w->type == WIDGET_BUTTON && w->on_click)
		w->on_click(w, gui);
	else if (w->type == WIDGET_TOGGLE)
	{
		w->value = !w->value;
		if (w->target)
			*(int *)w->target = w->value;
		if (w->on_change)
			w->on_change(w, gui);
	}
	else if (w->type == WIDGET_CHECKBOX && w->on_click)
		w->on_click(w, gui);
}

static void	dispatch_click(t_gui *gui, t_widget *w, t_vec2i mouse)
{
	if (w->type == WIDGET_MESSAGE_BOX)
		handle_msgbox_click(gui, w, mouse);
	else if (hit_titlebar(w, mouse))
	{
		gui->dragging_widget = w;
		w->being_dragged = true;
		w->drag_offset = vec2i((int)mouse.x - (int)w->pos.x,
				(int)mouse.y - (int)w->pos.y);
	}
	else if (hit_body(w, mouse))
		handle_control_click(gui, w, mouse);
}

void	widget_handle_mouse(struct s_gui *gui, int button, t_vec2i mouse)
{
	t_widget	*w;

	if (button != BUTTON_LEFT)
		return ;
	if (gui->focused_widget)
	{
		gui->focused_widget->focused = false;
		gui->focused_widget = NULL;
	}
	w = gui->widgets;
	while (w)
	{
		if (w->visible)
			dispatch_click(gui, w, mouse);
		w = w->next;
	}
}

void	widget_handle_motion(struct s_gui *gui, t_vec2i mouse)
{
	t_widget	*w;
	int			nx;
	int			ny;

	w = gui->dragging_widget;
	if (!w || !w->being_dragged)
		return ;
	nx = (int)mouse.x - (int)w->drag_offset.x;
	ny = (int)mouse.y - (int)w->drag_offset.y;
	if (nx < 0)
		nx = 0;
	if (ny < 0)
		ny = 0;
	w->pos.x = nx;
	w->pos.y = ny;
}

void	widget_handle_release(struct s_gui *gui)
{
	if (gui->dragging_widget)
	{
		gui->dragging_widget->being_dragged = false;
		gui->dragging_widget = NULL;
	}
	slider_end_drag(gui);
}
