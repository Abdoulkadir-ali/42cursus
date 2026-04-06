/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widget.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:07:46 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 12:33:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

void	widget_set_size(t_widget *widget, t_vec2s size)
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

t_widget	*widget_create(t_widget_type type, t_vec2i pos, t_vec2s size,
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
