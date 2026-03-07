/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widget.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:07:46 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:07:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

t_widget	*widget_create_type_pos(t_widget_type type, t_vec2i pos)
{
	t_widget *widget;

	widget = malloc(sizeof(t_widget));
	if (!widget)
		return (NULL);
	memset(widget, 0, sizeof(t_widget));
	widget->type = type;
	widget->pos = pos;
	return (widget);
}

void	widget_set_size(t_widget *widget, t_vec2i size)
{
	widget->size = size;
}

void	widget_set_label(t_widget *widget, const char *label)
{
	if (label)
		widget->label = strdup(label);
}

void	widget_add(t_gui *gui, t_widget *widget)
{
	widget->next = gui->widgets;
	gui->widgets = widget;
}

t_widget	*widget_create(t_widget_type type, t_vec2i pos, t_vec2i size,
		const char *label)
{
	t_widget *widget;

	widget = malloc(sizeof(t_widget));
	if (!widget)
		return (NULL);
	memset(widget, 0, sizeof(t_widget));
	widget->type = type;
	widget->pos = pos;
	widget->size = size;
	if (label)
		widget->label = strdup(label);
	return (widget);
}

void	widget_handle_mouse(struct s_gui *gui, int button, t_vec2i mouse)
{
	(void)button;
	t_widget *w;

	w = gui->widgets;
	while (w)
	{
		if (mouse.x >= w->pos.x && mouse.x < w->pos.x + w->size.x
			&& mouse.y >= w->pos.y && mouse.y < w->pos.y + w->size.y)
		{
			if (w->on_click)
				w->on_click(w, gui);
		}
		w = w->next;
	}
}
