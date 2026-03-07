/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_info_panel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/07 23:11:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"

static void	draw_info_row(t_gui *gui, int x, int y,
	const char *label, const char *val)
{
	mlx_string_put(gui->win.mlx, gui->win.win, x + 8, y, COL_HOVER,
		(char *)label);
	mlx_string_put(gui->win.mlx, gui->win.win, x + 96, y, COL_TEXT,
		(char *)val);
}

void	draw_mesh_info_panel(t_gui *gui, int x)
{
	t_mesh	*mesh;
	char	buf[64];
	int		y;

	if (!gui->scene || gui->selection.index >= gui->scene->mesh_count)
		return ;
	mesh = &gui->scene->meshes[gui->selection.index];
	mlx_string_put(gui->win.mlx, gui->win.win, x + 8, 88, COL_HOVER, "MESH INFO");
	y = 106;
	if (mesh->name)
		snprintf(buf, sizeof(buf), "%.24s", mesh->name);
	else
		snprintf(buf, sizeof(buf), "(unnamed)");
	draw_info_row(gui, x, y, "Name:", buf);
	y += 18;
	snprintf(buf, sizeof(buf), "%d", mesh->vertex_count);
	draw_info_row(gui, x, y, "Vertices:", buf);
	y += 18;
	snprintf(buf, sizeof(buf), "%d", mesh->tri_count);
	draw_info_row(gui, x, y, "Triangles:", buf);
	y += 18;
	snprintf(buf, sizeof(buf), "%d", mesh->anim_clip_count);
	draw_info_row(gui, x, y, "Animations:", buf);
	y += 18;
	snprintf(buf, sizeof(buf), "%d", mesh->current_anim);
	draw_info_row(gui, x, y, "Anim idx:", buf);
	y += 18;
	snprintf(buf, sizeof(buf), "%.2f  %.2f  %.2f",
		mesh->bbox.min.x, mesh->bbox.min.y, mesh->bbox.min.z);
	draw_info_row(gui, x, y, "BBox min:", buf);
	y += 18;
	snprintf(buf, sizeof(buf), "%.2f  %.2f  %.2f",
		mesh->bbox.max.x, mesh->bbox.max.y, mesh->bbox.max.z);
	draw_info_row(gui, x, y, "BBox max:", buf);
}
