/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
/**
 * @brief Handles click events in the scene hierarchy panel.
 * @param gui Pointer to the GUI context.
 * @param mouse Coordinates of the click.
 * @return true if handled.
 */
bool	scene_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	int		row;
	t_type	ty;
	int		idx;

	if (!gui->scene_panel->visible || !gui->scene)
		return (false);
	if (mouse.x < 0 || mouse.x >= gui->scene_panel->box.size.x)
		return (false);
	if (mouse.y >= 0 && mouse.y < CRUD_PANEL_H)
		return (crud_handle_click(gui, mouse));
	row = (mouse.y - CRUD_PANEL_H + gui->scene_panel->scroll) / ROW_H;
	if (row < 0 || row >= count_scene_rows(gui->scene))
		return (false);
	row_to_object(gui, row, &ty, &idx);
	if (ty == TYPE_NONE)
		return (true);
	select_object(gui, ty, idx);
	gui->render.dirty = true;
	return (true);
}
