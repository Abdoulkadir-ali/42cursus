/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 17:46:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

const char	*mesh_name(t_mesh *mesh)
{
	if (mesh->name)
		return (mesh->name);
	return ("(unnamed)");
}

/* keybinds and title are now drawn in the scene panel header */
void	draw_ui_help(t_gui *gui, int *y)
{
	(void)gui;
	(void)y;
}

/* physics status moved to scene panel header */
void	draw_ui_status(t_gui *gui, int *y)
{
	(void)gui;
	(void)y;
}

void	draw_ui_object(t_gui *gui)
{
	char	buf[128];
	t_mesh	*mesh;

	if (!gui || !gui->scene || gui->scene->mesh_count == 0)
		return ;
	mesh = &gui->scene->meshes[0];
	snprintf(buf, sizeof(buf), "Object: %s", mesh_name(mesh));
	mlx_string_put(gui->win.mlx, gui->win.win, 350, 38, 0xE0A820, buf);
	snprintf(buf, sizeof(buf), "Material: %zu", mesh->mat_id);
	mlx_string_put(gui->win.mlx, gui->win.win, 350, 58, 0xD0D0D8, buf);
	snprintf(buf, sizeof(buf), "Vertices: %zu", mesh->vertex_count);
	mlx_string_put(gui->win.mlx, gui->win.win, 350, 78, 0xD0D0D8, buf);
	snprintf(buf, sizeof(buf), "Transform: Pos(%.2f,%.2f,%.2f)",
		mesh->transform.pos.x, mesh->transform.pos.y, mesh->transform.pos.z);
	mlx_string_put(gui->win.mlx, gui->win.win, 350, 98, 0xD0D0D8, buf);
}
