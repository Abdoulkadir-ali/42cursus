/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 19:55:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	get_clicked_row(t_gui *gui, t_vec2i mouse)
{
	t_vec2s	d;
	int		y_off;
	int		row_h;

	d = gui->win.disp_size;
	y_off = mouse.y - ui_sy(CRUD_PANEL_H, d)
		+ ui_sy(gui->scene_panel.scroll, d);
	row_h = ui_sy(ROW_H, d);
	if (row_h <= 0)
		return (-1);
	return (y_off / row_h);
}

bool	scene_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_type	type;
	size_t	i;
	size_t	total;
	int		row;

	if (!gui->scene_panel.visible || !gui->scene)
		return (false);
	if (mouse.x >= (int)gui->scene_panel.width)
		return (false);
	if (crud_handle_click(gui, mouse))
		return (true);
	if (mouse.y < ui_sy(CRUD_PANEL_H, gui->win.disp_size))
		return (true);
	row = get_clicked_row(gui, mouse);
	total = count_scene_rows(gui->scene);
	if (row < 0 || (size_t)row >= total)
		return (false);
	row_to_object(gui, row, &type, &i);
	if (type == TYPE_NONE)
		return (true);
	select_object(gui, type, i);
	gui->render.dirty = true;
	return (true);
}
