/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:35:14 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 20:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

void	widget_physics_toggle(t_widget *w, t_gui *gui)
{
	gui->physics_enabled = !gui->physics_enabled;
	w->value = gui->physics_enabled;
	gui->render.dirty = true;
}

void	widget_init_default(t_gui *gui)
{
	t_widget	*cb;

	cb = widget_create(WIDGET_CHECKBOX, vec2i(32, 122), vec2s(180, 20),
			"Simulate Physics");
	if (cb)
	{
		cb->value = gui->physics_enabled;
		cb->on_click = widget_physics_toggle;
		widget_add(gui, cb);
	}
}
