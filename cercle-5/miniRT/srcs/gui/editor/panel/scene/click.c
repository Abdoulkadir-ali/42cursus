/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 14:02:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	calc_row_click(t_gui *gui, t_vec2i mouse)
{
	int	list_start;

	list_start = CRUD_PANEL_H + SCENE_PANEL_PAD_Y + 28;
	return ((mouse.y - list_start + gui->scene_panel->scroll) / ROW_H);
}

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
	row = calc_row_click(gui, mouse);
	if (row < 0 || row >= count_scene_rows(gui->scene))
		return (false);
	row_to_object(gui, row, &ty, &idx);
	if (ty == TYPE_NONE)
		return (true);
	select_object(gui, ty, idx);
	gui->render.dirty = true;
	return (true);
}
