/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 16:24:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
static void	dispatch_click(t_gui *gui, t_vec2i mouse)
{
	t_physics_body	*phys;

	if (gui->inspector->tab == TAB_MATERIAL)
		material_panel_handle_click(gui, mouse);
	else if (gui->inspector->tab == TAB_TRANSFORM)
		transform_panel_handle_click(gui, mouse);
	else if (gui->inspector->tab == TAB_PHYSICS)
	{
		phys = get_selected_physics(gui);
		if (phys)
			physics_panel_handle_click(gui, mouse, phys);
	}
	else if (gui->inspector->tab == TAB_LIGHT)
		light_panel_handle_click(gui, mouse);
	else if (gui->inspector->tab == TAB_OBJECT)
		metadata_panel_handle_click(gui, mouse);
}

/**
 * @brief Detects and handles mouse clicks on inspector tabs and sub-panels.
 * @param gui Pointer to the GUI.
 * @param mouse Cursor coordinates.
 * @return true if the event was captured, false otherwise.
 */
bool	inspector_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_inspect_tab	tabs[4];
	const char		*lbls[4];
	int				n;
	int				x;

	if (!gui->inspector->visible || !gui->selection->active)
		return (false);
	x = gui->win.disp_size.x - gui->inspector->box.size.x;
	if (mouse.x < x || mouse.x >= gui->win.disp_size.x)
		return (false);
	if (mouse.y >= INSPECTOR_TAB_MIN_Y && mouse.y <= INSPECTOR_TAB_MAX_Y)
	{
		n = get_tabs(gui->selection->type, tabs, lbls);
		n = (mouse.x - x) / (INSPECTOR_W / n);
		if (n >= 0 && n < get_tabs(gui->selection->type, tabs, lbls))
			gui->inspector->tab = tabs[n];
		return (true);
	}
	dispatch_click(gui, mouse);
	return (true);
}
