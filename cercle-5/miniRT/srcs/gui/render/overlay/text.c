/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:16:32 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:20:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_ui_help(t_gui *gui, int *y)
{
	mlx_string_put(gui->win.mlx, gui->win.win, 32, *y, COL_ACCENT, "miniRT");
	*y += 24;
	mlx_string_put(gui->win.mlx, gui->win.win, 32, *y, COL_TEXT,
		"WASD  Move   SPACE/SHIFT  Up/Down");
	*y += 20;
	mlx_string_put(gui->win.mlx, gui->win.win, 32, *y, COL_TEXT,
		"LMB   Look   MMB          Zoom");
	*y += 20;
	mlx_string_put(gui->win.mlx, gui->win.win, 32, *y, COL_TEXT,
		"+/-   Speed  N            Next map");
	*y += 20;
}

void	draw_ui_status(t_gui *gui, int *y)
{
	char	buf[128];

	snprintf(buf, sizeof(buf), "[ %c ] Simulate Physics",
		gui->physics_enabled ? 'X' : ' ');
	mlx_string_put(gui->win.mlx, gui->win.win, 32, *y, COL_TEXT, buf);
	*y += 20;
	snprintf(buf, sizeof(buf), "Ambient Intensity: %.2f",
		gui->ambient_intensity);
	mlx_string_put(gui->win.mlx, gui->win.win, 32, *y, COL_TEXT, buf);
	*y += 20;
	snprintf(buf, sizeof(buf), "Ambient Color: #%06X",
		gui->ambient_color & 0xFFFFFF);
	mlx_string_put(gui->win.mlx, gui->win.win, 32, *y, COL_TEXT, buf);
	*y += 20;
}

void	draw_ui_object(t_gui *gui)
{
	char	buf[128];
	t_mesh	*mesh;

	if (!gui->scene || gui->scene->mesh_count == 0)
		return ;
	mesh = &gui->scene->meshes[0];
	snprintf(buf, sizeof(buf), "Object: %s",
		mesh->name ? mesh->name : "(unnamed)");
	mlx_string_put(gui->win.mlx, gui->win.win, 350, 38, COL_ACCENT, buf);
	snprintf(buf, sizeof(buf), "Material: %d", mesh->mat_id);
	mlx_string_put(gui->win.mlx, gui->win.win, 350, 58, COL_TEXT, buf);
	snprintf(buf, sizeof(buf), "Vertices: %d", mesh->vertex_count);
	mlx_string_put(gui->win.mlx, gui->win.win, 350, 78, COL_TEXT, buf);
	snprintf(buf, sizeof(buf), "Transform: Pos(%.2f,%.2f,%.2f)",
		mesh->transform.pos.x, mesh->transform.pos.y, mesh->transform.pos.z);
	mlx_string_put(gui->win.mlx, gui->win.win, 350, 98, COL_TEXT, buf);
}
