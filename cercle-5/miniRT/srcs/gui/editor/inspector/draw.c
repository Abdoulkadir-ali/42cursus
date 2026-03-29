/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 16:21:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
static void	draw_tabs(t_gui *gui, int x)
{
	t_inspect_tab	tabs[MAX_INSPECT_TABS];
	const char		*labels[MAX_INSPECT_TABS];
	int				n[4];

	n[0] = get_tabs(gui->selection->type, tabs, labels);
	n[1] = INSPECTOR_W / n[0];
	n[2] = 0;
	while (n[2] < n[0])
	{
		n[3] = COL_TEXT;
		if (gui->inspector->tab == tabs[n[2]])
			n[3] = COL_ACCENT;
		gui_draw_string(gui, (char *)labels[n[2]], x + n[1] * n[2] + INSPECTOR_PAD, INSPECTOR_TAB_Y, n[3]);
		n[2]++;
	}
}

static void	dispatch_draw(t_gui *gui, int x)
{
	t_physics_body	*phys;

	if (gui->inspector->tab == TAB_TRANSFORM)
		draw_transform_panel(gui, x);
	else if (gui->inspector->tab == TAB_MATERIAL)
		draw_material_panel_text(gui, x);
	else if (gui->inspector->tab == TAB_PHYSICS)
	{
		phys = get_selected_physics(gui);
		if (phys)
			draw_physics_panel(gui, phys, x);
	}
	else if (gui->inspector->tab == TAB_LIGHT)
		draw_light_panel(gui, x);
	else if (gui->inspector->tab == TAB_OBJECT)
		draw_metadata_panel(gui, x);
	else if (gui->inspector->tab == TAB_INFO)
		draw_mesh_info_panel(gui, x);
}

/**
 * @brief Public entrance to draw the active inspector panel and its tabs.
 * @param gui Pointer to the GUI.
 */
void	draw_inspector_text(t_gui *gui)
{
	int		x;
	char	buf[64];

	if (!gui->inspector->visible || !gui->selection->active || !gui->scene)
		return ;
	x = gui->win.disp_size.x - gui->inspector->box.size.x;
	snprintf(buf, sizeof(buf), "%s  #%d",
		type_name_str(gui->selection->type), gui->selection->index);
	gui_draw_string(gui, buf, x + INSPECTOR_PAD, INSPECTOR_HDR_Y, COL_ACCENT);
	draw_tabs(gui, x);
	dispatch_draw(gui, x);
}
