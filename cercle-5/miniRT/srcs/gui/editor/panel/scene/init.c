/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:56:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
void	editor_init(t_gui *gui)
{
	gui->scene_panel.visible = true;
	gui->scene_panel.width = SCENE_PANEL_W;
	gui->scene_panel.scroll = 0;
	gui->scene_panel.hovered_row = -1;
	gui->inspector.visible = false;
	gui->inspector.width = INSPECTOR_W;
	gui->inspector.tab = TAB_TRANSFORM;
	gui->selection.active = false;
	gui->selection.type = TYPE_NONE;
	gui->selection.index = -1;
}
