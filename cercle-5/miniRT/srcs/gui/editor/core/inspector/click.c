/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static bool	handle_tab_click(t_gui *gui, t_vec2i mouse, int x)
{
	t_vec2s			d;
	t_inspect_tab	tabs[4];
	const char		*labels[4];
	int				count;
	int				idx;

	d = gui->win.disp_size;
	count = get_tabs(gui->selection.type, tabs, labels);
	if (mouse.y >= ui_sy(60, d) && mouse.y <= ui_sy(84, d))
	{
		idx = (mouse.x - x) / (gui->inspector.width / count);
		if (idx >= 0 && idx < count)
			gui->inspector.tab = tabs[idx];
		return (true);
	}
	return (false);
}

static void	dispatch_tab_click(t_gui *gui, t_vec2i mouse)
{
	t_physics_body	*phys;

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
	else if (gui->inspector.tab == TAB_INFO)
		info_panel_handle_click(gui, mouse);
}

bool	inspector_handle_click(t_gui *gui, t_vec2i mouse)
{
	int	x;
	int	dw;

	if (!gui->inspector.visible || !gui->selection.active)
		return (false);
	dw = gui->win.disp_size.x;
	x = dw - gui->inspector.width;
	if (mouse.x < x || mouse.x >= dw)
		return (false);
	if (handle_tab_click(gui, mouse, x))
		return (true);
	dispatch_tab_click(gui, mouse);
	return (true);
}
