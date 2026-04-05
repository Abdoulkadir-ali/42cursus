/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widget.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:07:46 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"
#include <X11/keysym.h>

void	widget_set_size(t_widget *widget, t_vec2i size)
{
	widget->size = size;
}

void	widget_set_label(t_widget *widget, const char *label)
{
	if (label)
		widget->label = ft_strdup(label);
}

void	widget_add(t_gui *gui, t_widget *widget)
{
	widget->next = gui->widgets;
	gui->widgets = widget;
}

t_widget	*widget_create(t_widget_type type, t_vec2i pos, t_vec2i size,
		const char *label)
{
	t_widget	*widget;

	widget = malloc(sizeof(t_widget));
	if (!widget)
		return (NULL);
	ft_memset(widget, 0, sizeof(t_widget));
	widget->type = type;
	widget->pos = pos;
	widget->size = size;
	widget->visible = true;
	if (label)
		widget->label = ft_strdup(label);
	return (widget);
}

/* ── INTERNAL HIT TESTS ──────────────────────────────────────────────────── */

static bool	hit_titlebar(t_widget *w, t_vec2i m)
{
	return (w->draggable
		&& (int)m.x >= (int)w->pos.x
		&& (int)m.x < (int)w->pos.x + (int)w->size.x
		&& (int)m.y >= (int)w->pos.y
		&& (int)m.y < (int)w->pos.y + WIDGET_TITLE_H);
}

static bool	hit_body(t_widget *w, t_vec2i m)
{
	int	top;

	top = w->draggable ? (int)w->pos.y + WIDGET_TITLE_H : (int)w->pos.y;
	return ((int)m.x >= (int)w->pos.x
		&& (int)m.x < (int)w->pos.x + (int)w->size.x
		&& (int)m.y >= top
		&& (int)m.y < (int)w->pos.y + (int)w->size.y);
}

/* ── MOUSE CLICK ─────────────────────────────────────────────────────────── */

static bool	handle_msgbox_click(t_gui *gui, t_widget *w, t_vec2i m)
{
	int	bw;
	int	bx;
	int	by;
	int	i;

	if (!w->visible)
		return (false);
	bw = (w->size.x - 16) / (w->btn_count > 0 ? w->btn_count : 1);
	by = (int)w->pos.y + w->size.y - 28;
	i = 0;
	while (i < w->btn_count)
	{
		bx = (int)w->pos.x + 8 + i * (bw + 4);
		if ((int)m.x >= bx && (int)m.x < bx + bw - 4
			&& (int)m.y >= by && (int)m.y < by + 22)
		{
			if (w->btn_callbacks[i])
				w->btn_callbacks[i](w, gui);
			return (true);
		}
		i++;
	}
	return ((int)m.x >= (int)w->pos.x
		&& (int)m.x < (int)w->pos.x + (int)w->size.x
		&& (int)m.y >= (int)w->pos.y + 24
		&& (int)m.y < (int)w->pos.y + (int)w->size.y);
}

void	widget_handle_mouse(struct s_gui *gui, int button, t_vec2i mouse)
{
	t_widget	*w;

	if (button != BUTTON_LEFT)
		return ;
	/* unfocus current focus */
	if (gui->focused_widget)
	{
		gui->focused_widget->focused = false;
		gui->focused_widget = NULL;
	}
	w = gui->widgets;
	while (w)
	{
		if (w->type == WIDGET_MESSAGE_BOX)
		{
			if (handle_msgbox_click(gui, w, mouse))
				return ;
			w = w->next;
			continue ;
		}
		/* title bar drag */
		if (hit_titlebar(w, mouse))
		{
			gui->dragging_widget = w;
			w->being_dragged = true;
			w->drag_offset = vec2i((int)mouse.x - (int)w->pos.x,
					(int)mouse.y - (int)w->pos.y);
			return ;
		}
		if (!hit_body(w, mouse))
		{
			w = w->next;
			continue ;
		}
		/* focus for input box */
		if (w->type == WIDGET_INPUT_BOX)
		{
			w->focused = true;
			gui->focused_widget = w;
		}
		/* slider */
		if (w->type == WIDGET_SLIDER)
			slider_handle_click(gui, w, mouse);
		/* button */
		else if (w->type == WIDGET_BUTTON && w->on_click)
			w->on_click(w, gui);
		/* toggle */
		else if (w->type == WIDGET_TOGGLE)
		{
			w->value = !w->value;
			if (w->target)
				*(int *)w->target = w->value;
			if (w->on_change)
				w->on_change(w, gui);
		}
		/* checkbox */
		else if (w->type == WIDGET_CHECKBOX)
		{
			if (w->on_click)
				w->on_click(w, gui);
		}
		w = w->next;
	}
}

/* ── MOUSE MOTION (drag) ─────────────────────────────────────────────────── */

void	widget_handle_motion(struct s_gui *gui, t_vec2i mouse)
{
	t_widget	*w;

	w = gui->dragging_widget;
	if (!w || !w->being_dragged)
		return ;
	if ((int)mouse.x < (int)w->drag_offset.x)
		w->pos.x = 0;
	else
		w->pos.x = (int)mouse.x - (int)w->drag_offset.x;
	if ((int)mouse.y < (int)w->drag_offset.y)
		w->pos.y = 0;
	else
		w->pos.y = (int)mouse.y - (int)w->drag_offset.y;
}

/* ── MOUSE RELEASE ───────────────────────────────────────────────────────── */

void	widget_handle_release(struct s_gui *gui)
{
	if (gui->dragging_widget)
	{
		gui->dragging_widget->being_dragged = false;
		gui->dragging_widget = NULL;
	}
	slider_end_drag(gui);
}

