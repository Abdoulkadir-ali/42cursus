/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:32:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

bool	scene_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	int		row;
	size_t	total;
	t_type	ty;
	int		idx;

	if (!gui->scene_panel.visible || !gui->scene)
		return (false);
	if (mouse.x >= gui->scene_panel.width)
		return (false);
	if (mouse.y < CRUD_PANEL_H)
		return (crud_handle_click(gui, mouse));
	row = (mouse.y - CRUD_PANEL_H + gui->scene_panel.scroll) / ROW_H;
	total = count_scene_rows(gui->scene);
	if (row < 0 || (size_t)row >= total)
		return (false);
	row_to_object(gui, row, &ty, &idx);
	if (ty == TYPE_NONE)
		return (true);
	select_object(gui, ty, idx);
	gui->render.dirty = true;
	return (true);
}
