/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 18:51:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	gui_recompute_layout(t_gui *gui)
{
	size_t	w;

	w = gui->win.disp_size.x;
	gui->scene_panel.width = w * 16 / 100;
	if (gui->scene_panel.width < 180)
		gui->scene_panel.width = 180;
	gui->inspector.width = (int)(w * 22 / 100);
	if (gui->inspector.width < 220)
		gui->inspector.width = 220;
}

void	editor_init(t_gui *gui)
{
	gui->scene_panel.visible = true;
	gui->scene_panel.scroll = 0;
	gui->scene_panel.hovered_row = -1;
	gui->inspector.visible = false;
	gui->inspector.tab = TAB_TRANSFORM;
	gui->selection.active = false;
	gui->selection.type = TYPE_NONE;
	gui->selection.index = -1;
	gui_recompute_layout(gui);
}
