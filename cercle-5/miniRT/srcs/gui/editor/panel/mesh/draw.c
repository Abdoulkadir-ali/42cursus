/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:55:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/28 16:24:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static t_mesh_instance_metadata	*selected_mesh_instance_meta(t_gui *gui)
{
	int	idx;

	if (!gui->scene || !gui->scene->mesh_instance_meta)
		return (NULL);
	if (!gui->selection->active || gui->selection->type != TYPE_MESH)
		return (NULL);
	idx = gui->selection->index;
	if (idx < 0 || (size_t)idx >= gui->scene->mesh_count)
		return (NULL);
	return (gui->scene->mesh_instance_meta[idx]);
}

void	draw_mesh_info_panel(t_gui *gui, int x)
{
	t_mesh_instance_metadata	*m;
	char				buf[96];
	int					y;

	if (!gui->scene)
		return ;
	gui_draw_string(gui, "MESH INFO", x + 8, 88, COL_HOVER);
	m = selected_mesh_instance_meta(gui);
	y = 106;
	if (!m)
	{
		snprintf(buf, sizeof(buf), "Loaded meshes: %zu", gui->scene->mesh_count);
		gui_draw_string(gui, buf, x + 8, y, COL_TEXT);
		return ;
	}
	snprintf(buf, sizeof(buf), "Imported: %ld", (long)m->import_time);
	gui_draw_string(gui, buf, x + 8, y, COL_TEXT);
	y += 18;
	snprintf(buf, sizeof(buf), "Pos: %.2f %.2f %.2f", m->orig_transform.m[0][3],
		m->orig_transform.m[1][3], m->orig_transform.m[2][3]);
	gui_draw_string(gui, buf, x + 8, y, COL_TEXT);
	y += 18;
	if (m->file_path)
		snprintf(buf, sizeof(buf), "File: %.80s", m->file_path);
	else
		ft_strlcpy(buf, "File: n/a", sizeof(buf));
	gui_draw_string(gui, buf, x + 8, y, COL_TEXT);
}
