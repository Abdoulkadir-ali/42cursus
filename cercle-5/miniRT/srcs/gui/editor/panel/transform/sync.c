/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 19:56:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	transform_selection_sync(t_gui *gui)
{
	t_scene	*sc;

	sc = gui->scene;
	if (gui->selection.type == TYPE_SPHERE)
	{
		sc->spheres[gui->selection.index].pos = gui->transform.pos;
		sphere_scale_sync(gui);
	}
	else if (gui->selection.type == TYPE_PLANE)
	{
		sc->planes[gui->selection.index].pos = gui->transform.pos;
		sc->planes[gui->selection.index].normal = vec3_norm(
				mat4_mul_vec3(mat4_rotation(gui->transform.rotation),
					(t_vec3){0, 1, 0}));
	}
	else if (gui->selection.type == TYPE_MESH)
		mesh_transform_sync(gui);
	else if (gui->selection.type == TYPE_LIGHT)
		sc->lights[gui->selection.index].pos = gui->transform.pos;
}

void	transform_panel_sync(t_gui *gui)
{
	t_scene	*sc;

	sc = gui->scene;
	if (gui->selection.type == TYPE_SPHERE)
		gui->transform.pos = sc->spheres[gui->selection.index].pos;
	else if (gui->selection.type == TYPE_PLANE)
		gui->transform.pos = sc->planes[gui->selection.index].pos;
	else if (gui->selection.type == TYPE_MESH)
		gui->transform.pos = sc->groups[gui->selection.index].transform.pos;
	else if (gui->selection.type == TYPE_LIGHT)
		gui->transform.pos = sc->lights[gui->selection.index].pos;
}
