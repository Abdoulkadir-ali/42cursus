/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 19:31:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

bool	scene_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_vec2i	d;
	int		row;
	size_t	total;
	t_type	ty;
	int		idx;

	d = gui->win.disp_size;
	if (!gui->scene_panel.visible || !gui->scene)
		return (false);
	if (mouse.x >= gui->scene_panel.width)
		return (false);
	if (mouse.y < (size_t)ui_sy(CRUD_PANEL_H, d))
		return (crud_handle_click(gui, mouse));
	row = ((int)mouse.y - ui_sy(CRUD_PANEL_H, d) + ui_sy(gui->scene_panel.scroll, d))
		/ ui_sy(ROW_H, d);
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
