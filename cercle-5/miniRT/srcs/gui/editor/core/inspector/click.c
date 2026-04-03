/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:33:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static bool	handle_tab_click(t_gui *gui, t_vec2i mouse, int x)
{
	t_inspect_tab	tabs[4];
	const char		*labels[4];
	int				n;
	int				step;
	int				idx;

	n = get_tabs(gui->selection.type, tabs, labels);
	step = INSPECTOR_W / n;
	if (mouse.y >= 60 && mouse.y <= 84)
	{
		idx = (mouse.x - x) / step;
		if (idx >= 0 && idx < n)
			gui->inspector.tab = tabs[idx];
		return (true);
	}
	return (false);
}

bool	inspector_handle_click(t_gui *gui, t_vec2i mouse)
{
	size_t			x;
	t_physics_body	*phys;

	if (!gui->inspector.visible || !gui->selection.active)
		return (false);
	x = gui->win.disp_size.x - gui->inspector.width;
	if (mouse.x < x || mouse.x >= gui->win.disp_size.x)
		return (false);
	if (handle_tab_click(gui, mouse, x))
		return (true);
	if (gui->inspector.tab == TAB_MATERIAL)
		material_panel_handle_click(gui, mouse);
	else if (gui->inspector.tab == TAB_TRANSFORM)
		transform_panel_handle_click(gui, mouse);
	else if (gui->inspector.tab == TAB_PHYSICS)
	{
		phys = get_selected_physics(gui);
		if (phys)
			physics_panel_handle_click(gui, mouse, phys);
	}
	else if (gui->inspector.tab == TAB_LIGHT)
		light_panel_handle_click(gui, mouse);
	return (true);
}
