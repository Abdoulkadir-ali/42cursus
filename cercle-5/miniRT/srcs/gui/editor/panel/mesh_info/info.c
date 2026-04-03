/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:28:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_bbox_info(t_gui *gui, t_mesh *mesh, t_vec2i pos, int *y)
{
	char	buf[64];

	snprintf(buf, sizeof(buf), "%.2f  %.2f  %.2f",
		mesh->bbox.min.x, mesh->bbox.min.y, mesh->bbox.min.z);
	*y += 18;
	draw_info_row(gui, (t_vec2i){pos.x, *y}, "BBox min:", buf);
	snprintf(buf, sizeof(buf), "%.2f  %.2f  %.2f",
		mesh->bbox.max.x, mesh->bbox.max.y, mesh->bbox.max.z);
	*y += 18;
	draw_info_row(gui, (t_vec2i){pos.x, *y}, "BBox max:", buf);
}

void	draw_mesh_info_panel(t_gui *gui, t_vec2i pos)
{
	t_mesh_group	*g;
	t_mesh			*mesh;
	char			buf[64];
	int				y;

	if (!gui->scene || gui->selection.index >= gui->scene->group_count)
		return ;
	g = &gui->scene->groups[gui->selection.index];
	mesh = &gui->scene->meshes[g->start];
	mlx_string_put(gui->win.mlx, gui->win.win, pos.x + 8, 88, COL_HOVER,
		"MESH INFO");
	y = 106;
	if (g->name)
		snprintf(buf, sizeof(buf), "%.24s", g->name);
	else
		snprintf(buf, sizeof(buf), "(unnamed)");
	draw_info_row(gui, (t_vec2i){pos.x, y}, "Name:", buf);
	snprintf(buf, sizeof(buf), "%zu", g->sub_count);
	draw_info_row(gui, (t_vec2i){pos.x, y += 18}, "Sub-meshes:", buf);
	snprintf(buf, sizeof(buf), "%zu", mesh->vertex_count);
	draw_info_row(gui, (t_vec2i){pos.x, y += 18}, "Vertices[0]:", buf);
	snprintf(buf, sizeof(buf), "%zu", mesh->tri_count);
	draw_info_row(gui, (t_vec2i){pos.x, y += 18}, "Triangles[0]:", buf);
	draw_bbox_info(gui, mesh, pos, &y);
}
