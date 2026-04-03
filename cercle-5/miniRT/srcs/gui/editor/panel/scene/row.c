/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:56:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

const char	*row_type_prefix(t_type type)
{
	if (type == TYPE_LIGHT)
		return ("[LT]");
	if (type == TYPE_SPHERE)
		return ("[SP]");
	if (type == TYPE_PLANE)
		return ("[PL]");
	if (type == TYPE_CYLINDER)
		return ("[CY]");
	if (type == TYPE_CONE)
		return ("[CO]");
	if (type == TYPE_TRI)
		return ("[TR]");
	if (type == TYPE_RECT)
		return ("[RC]");
	if (type == TYPE_PYRAMID)
		return ("[PY]");
	if (type == TYPE_BOX)
		return ("[BX]");
	if (type == TYPE_CAPSULE)
		return ("[CA]");
	if (type == TYPE_MESH)
		return ("[ME]");
	return ("[??]");
}

void	draw_one_row(t_gui *gui, int y_px, t_type ty, int idx)
{
	char	buf[64];
	int		col;

	col = COL_TEXT;
	if (gui->selection.active && gui->selection.type == ty
		&& gui->selection.index == (size_t)idx)
		col = COL_SELECTED;
	if (ty == TYPE_MESH && idx >= 0
		&& (size_t)idx < gui->scene->group_count
		&& gui->scene->groups[idx].name)
	{
		snprintf(buf, sizeof(buf), "[ME] %.55s",
			gui->scene->groups[idx].name);
	}
	else
		snprintf(buf, sizeof(buf), "%s %d", row_type_prefix(ty), idx);
	mlx_string_put(gui->win.mlx, gui->win.win, 12, y_px, col, buf);
}

void	draw_scene_rows(t_gui *gui)
{
	int		total;
	int		row;
	int		y_px;
	t_type	ty;
	int		idx;

	total = count_scene_rows(gui->scene);
	row = 0;
	y_px = (CRUD_PANEL_H + 8) - gui->scene_panel.scroll;
	while (row < total && y_px < gui->win.disp_size.y - 8)
	{
		if (y_px >= (CRUD_PANEL_H + 4))
		{
			row_to_object(gui, row, &ty, &idx);
			draw_one_row(gui, y_px, ty, idx);
		}
		y_px += ROW_H;
		row++;
	}
}
