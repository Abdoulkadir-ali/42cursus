/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_mesh_basic_info(t_gui *gui, t_mesh_group *g, t_mesh *mesh,
				t_vec2i pos)
{
	char	buf[64];
	t_vec2s	d;
	int		y;

	d = gui->win.disp_size;
	y = ui_sy(106, d);
	if (g && g->name)
		snprintf(buf, sizeof(buf), "%.24s", g->name);
	else if (mesh->name)
		snprintf(buf, sizeof(buf), "%.24s", mesh->name);
	else
		snprintf(buf, sizeof(buf), "(unnamed)");
	draw_info_row(gui, (t_vec2i){pos.x, y}, "Name:", buf);
	if (g)
		snprintf(buf, sizeof(buf), "%zu", g->mesh_count);
	else
		snprintf(buf, sizeof(buf), "1");
	y += ui_sy(18, d);
	draw_info_row(gui, (t_vec2i){pos.x, y}, "Sub-meshes:", buf);
	snprintf(buf, sizeof(buf), "%zu", mesh->vertex_count);
	y += ui_sy(18, d);
	draw_info_row(gui, (t_vec2i){pos.x, y}, "Vertices:", buf);
	snprintf(buf, sizeof(buf), "%zu", mesh->tri_count);
	y += ui_sy(18, d);
	draw_info_row(gui, (t_vec2i){pos.x, y}, "Triangles:", buf);
}

void	set_mesh_ptr(t_gui *gui, t_mesh_group **g, t_mesh **mesh)
{
	if (gui->scene->group_count > 0
		&& gui->selection.index.i < gui->scene->group_count)
	{
		*g = &gui->scene->groups[gui->selection.index.i];
		*mesh = &gui->scene->meshes[(*g)->mesh_start];
	}
	else if (gui->selection.index.i < gui->scene->mesh_count)
	{
		*g = NULL;
		*mesh = &gui->scene->meshes[gui->selection.index.i];
	}
}
