/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 17:56:47 by abdoali          ###   ########.fr       */
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

void	draw_one_row(t_gui *gui, int y_px, t_type ty, size_t i)
{
	char	buf[64];
	int		col;

	col = COL_TEXT;
	if (gui->selection.active && gui->selection.type == ty
		&& gui->selection.index.i == i)
		col = COL_SELECTED;
	if (ty == TYPE_MESH && i < gui->scene->group_count
		&& gui->scene->groups[i].name)
		snprintf(buf, sizeof(buf), "[ME] %.55s", gui->scene->groups[i].name);
	else
		snprintf(buf, sizeof(buf), "%s %zu", row_type_prefix(ty), i);
	mlx_string_put_c(gui->win.mlx, gui->win.win, ui_sx(12, gui->win.disp_size),
		y_px, col, buf);
}

void	draw_scene_rows(t_gui *gui)
{
	size_t	total;
	size_t	row;
	int		y_px;
	t_type	ty;
	size_t	i;

	total = count_scene_rows(gui->scene);
	row = 0;
	y_px = ui_sy(CRUD_PANEL_H + 24, gui->win.disp_size)
		- ui_sy(gui->scene_panel.scroll, gui->win.disp_size);
	while (row < total && y_px < (int)gui->win.disp_size.y
		- ui_sy(8, gui->win.disp_size))
	{
		if (y_px >= ui_sy(CRUD_PANEL_H + 20, gui->win.disp_size))
		{
			row_to_object(gui, row, &ty, &i);
			draw_one_row(gui, y_px, ty, i);
		}
		y_px += ui_sy(ROW_H, gui->win.disp_size);
		row++;
	}
}
