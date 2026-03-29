/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 17:20:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/28 16:24:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static bool	is_prim_meta_type(t_type type)
{
	if (type == TYPE_SPHERE || type == TYPE_PLANE || type == TYPE_CYLINDER
		|| type == TYPE_CONE || type == TYPE_TRI || type == TYPE_RECT
		|| type == TYPE_PYRAMID || type == TYPE_BOX || type == TYPE_CAPSULE)
		return (true);
	return (false);
}

static t_primitive_metadata	*get_prim_meta(t_gui *gui)
{
	int	idx;

	if (!gui->selection->active || !gui->scene)
		return (NULL);
	if (!is_prim_meta_type(gui->selection->type) || !gui->scene->prim_meta)
		return (NULL);
	idx = gui->selection->index;
	if (idx < 0 || (size_t)idx >= gui->scene->primitives.count)
		return (NULL);
	return (&gui->scene->prim_meta[idx]);
}

static t_mesh_instance_metadata	*get_mesh_instance_meta(t_gui *gui)
{
	int	idx;

	if (!gui->selection->active || gui->selection->type != TYPE_MESH)
		return (NULL);
	if (!gui->scene || !gui->scene->mesh_instance_meta)
		return (NULL);
	idx = gui->selection->index;
	if (idx < 0 || (size_t)idx >= gui->scene->mesh_count)
		return (NULL);
	return (gui->scene->mesh_instance_meta[idx]);
}

static int	draw_line(t_gui *gui, int x, int y, const char *txt)
{
	gui_draw_string(gui, (char *)txt, x + 8, y, COL_TEXT);
	return (y + 18);
}

static int	draw_prim_meta(t_gui *gui, int x, int y, t_primitive_metadata *m)
{
	char	buf[128];

	if (!m)
		return (draw_line(gui, x, y, "No primitive metadata"));
	snprintf(buf, sizeof(buf), "Imported: %ld", (long)m->import_time);
	y = draw_line(gui, x, y, buf);
	snprintf(buf, sizeof(buf), "Pos: %.2f %.2f %.2f", m->orig_px,
		m->orig_py, m->orig_pz);
	y = draw_line(gui, x, y, buf);
	snprintf(buf, sizeof(buf), "Axis: %.2f %.2f %.2f", m->orig_ax,
		m->orig_ay, m->orig_az);
	y = draw_line(gui, x, y, buf);
	snprintf(buf, sizeof(buf), "Radius: %.2f", m->orig_radii);
	y = draw_line(gui, x, y, buf);
	snprintf(buf, sizeof(buf), "Height: %.2f", m->orig_heights);
	y = draw_line(gui, x, y, buf);
	if (m->file_path)
		snprintf(buf, sizeof(buf), "File: %.84s", m->file_path);
	else
		ft_strlcpy(buf, "File: n/a", sizeof(buf));
	y = draw_line(gui, x, y, buf);
	if (m->user_comment)
		snprintf(buf, sizeof(buf), "Comment: %.80s", m->user_comment);
	else
		ft_strlcpy(buf, "Comment: n/a", sizeof(buf));
	return (draw_line(gui, x, y, buf));
}

static int	draw_mesh_instance_meta(t_gui *gui, int x, int y, t_mesh_instance_metadata *m)
{
	char	buf[128];

	if (!m)
		return (draw_line(gui, x, y, "No mesh metadata"));
	snprintf(buf, sizeof(buf), "Imported: %ld", (long)m->import_time);
	y = draw_line(gui, x, y, buf);
	snprintf(buf, sizeof(buf), "Pos: %.2f %.2f %.2f", m->orig_transform.m[0][3],
		m->orig_transform.m[1][3], m->orig_transform.m[2][3]);
	y = draw_line(gui, x, y, buf);
	if (m->file_path)
		snprintf(buf, sizeof(buf), "File: %.84s", m->file_path);
	else
		ft_strlcpy(buf, "File: n/a", sizeof(buf));
	return (draw_line(gui, x, y, buf));
}

void	draw_metadata_panel(t_gui *gui, int x)
{
	t_primitive_metadata		*pm;
	t_mesh_instance_metadata	*mm;
	int					y;

	gui_draw_string(gui, "METADATA", x + 8, 88, COL_HOVER);
	y = 106;
	pm = get_prim_meta(gui);
	if (pm)
	{
		y = draw_prim_meta(gui, x, y, pm);
		gui_draw_string(gui, "Reset to import", x + 8, y + 12, COL_ACCENT);
		return ;
	}
	mm = get_mesh_instance_meta(gui);
	if (mm)
	{
		draw_mesh_instance_meta(gui, x, y, mm);
		return ;
	}
	draw_line(gui, x, y, "No metadata for selection");
}
