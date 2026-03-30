/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 20:02:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void	draw_bbox_info(t_gui *gui, t_mesh *mesh, t_vec2 pos, int *y)
{
	char	buf[64];

	snprintf(buf, sizeof(buf), "%.2f  %.2f  %.2f",
		mesh->bbox.min.x, mesh->bbox.min.y, mesh->bbox.min.z);
	*y += 18;
	draw_info_row(gui, (t_vec2){pos.x, *y}, "BBox min:", buf);
	snprintf(buf, sizeof(buf), "%.2f  %.2f  %.2f",
		mesh->bbox.max.x, mesh->bbox.max.y, mesh->bbox.max.z);
	*y += 18;
	draw_info_row(gui, (t_vec2){pos.x, *y}, "BBox max:", buf);
}

void	draw_mesh_info_panel(t_gui *gui, int x)
{
	t_mesh_group	*g;
	t_mesh			*mesh;
	char			buf[64];
	int				y;

	if (!gui->scene || gui->selection.index >= gui->scene->group_count)
		return ;
	g = &gui->scene->groups[gui->selection.index];
	mesh = &gui->scene->meshes[g->start];
	mlx_string_put(gui->win.mlx, gui->win.win, x + 8, 88, COL_HOVER,
		"MESH INFO");
	y = 106;
	if (g->name)
		snprintf(buf, sizeof(buf), "%.24s", g->name);
	else
		snprintf(buf, sizeof(buf), "(unnamed)");
	draw_info_row(gui, (t_vec2){x, y}, "Name:", buf);
	snprintf(buf, sizeof(buf), "%d", g->sub_count);
	draw_info_row(gui, (t_vec2){x, y += 18}, "Sub-meshes:", buf);
	snprintf(buf, sizeof(buf), "%d", mesh->vertex_count);
	draw_info_row(gui, (t_vec2){x, y += 18}, "Vertices[0]:", buf);
	snprintf(buf, sizeof(buf), "%d", mesh->tri_count);
	draw_info_row(gui, (t_vec2){x, y += 18}, "Triangles[0]:", buf);
	draw_bbox_info(gui, mesh, (t_vec2){x, 0}, &y);
}
